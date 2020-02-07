use std::cmp::min;
use std::borrow::BorrowMut;
use std::io;
use std::str;
use io::Write;

#[derive(Default)]
pub struct Scanner<R> {
	reader: R,
	buffer: Vec<String>,
}

impl<R: io::BufRead> Scanner<R> {
	pub fn new(reader: R) -> Self {
		Self {
			reader,
			buffer: Vec::new(),
		}
	}

	/// Use "turbofish" syntax token::<T>() to select data type of next token.
	///
	/// # Panics
	///
	/// Panics if there's an I/O error or if the token cannot be parsed as T.
	pub fn next<T: str::FromStr>(&mut self) -> T {
		loop {
			if let Some(token) = self.buffer.pop() {
				return token.parse().ok().expect("Failed parse");
			}
			let mut input = String::new();
			self.reader.read_line(&mut input).expect("Failed read");
			self.buffer = input.split_whitespace().rev().map(String::from).collect();
		}
	}
}

pub fn scanner_from_file(filename: &str) -> Scanner<io::BufReader<std::fs::File>> {
	let file = std::fs::File::open(filename).expect("Input file not found");
	Scanner::new(io::BufReader::new(file))
}

pub fn writer_to_file(filename: &str) -> io::BufWriter<std::fs::File> {
	let file = std::fs::File::create(filename).expect("Output file not found");
	io::BufWriter::new(file)
}

// Common graph representation.
struct Graph {
	n_vertex: usize,
	adjs: Vec<Vec<usize>>,
}

impl Graph {
	pub fn new(v: usize) -> Self {
		Self {
			n_vertex: v,
			adjs: vec![vec![]; v]
		}
	}

	pub fn add_directed_edge(&mut self, u: usize, v:usize) {
		self.adjs[u].push(v);
	}
}

// Build strongly connected components.
struct StronglyConnectedComponents {
	sccs: Vec<Vec<usize>>,  // The strongly connected components.
	num: Vec<i32>,
	low: Vec<i32>,
	current: Vec<bool>,
	st: Vec<usize>,
	counter: i32,
}

impl StronglyConnectedComponents {
	pub fn new(graph: &Graph) -> Self {
		let v = graph.n_vertex;
		Self {
			sccs: vec![],
			num: vec![-1; v],
			low: vec![0; v],
			current: vec![false; v],
			st: vec![],
			counter: 0,
		}
	}
}

impl Graph {
	pub fn build_scc(&self) -> StronglyConnectedComponents {
		let mut result = StronglyConnectedComponents::new(self);
		for u in 0..self.n_vertex {
			if result.num[u] < 0 {
				self.dfs(u, result.borrow_mut());
			}
		}
		result
	}

	fn dfs(&self, u: usize, result: &mut StronglyConnectedComponents) {
		result.low[u] = result.counter;
		result.num[u] = result.counter;
		result.counter += 1;

		result.st.push(u);
		result.current[u] = true;

		for &v in self.adjs[u].iter() {
			if result.num[v] == -1 {
				self.dfs(v, result);
			}
			if result.current[v] {
				result.low[u] = min(result.low[u], result.low[v]);
			}
		}

		if result.low[u] == result.num[u] {
			let mut scc = vec![];
			while let Some(v) = result.st.pop() {
				result.current[v] = false;
				scc.push(v);
				if u == v {
					break;
				}
			}
			result.sccs.push(scc);
		}
	}
}

fn main() {
	let mut scanner = scanner_from_file("floyd.in");
	let mut writer = writer_to_file("floyd.out");

	let n = scanner.next::<usize>();
	let mut s = scanner.next::<i64>();
	let mut graph = Graph::new(n);

	// Build original graph.
	let mut d = vec![vec![0; n]; n];
	for i in 0..n {
		for j in 0..n {
			if i == j {
				continue
			}

			d[i][j] = (s % 1000) as i32;
			s = s * 16807 % 2147483647;

			if d[i][j] == 0 {
				graph.add_directed_edge(i, j);
			}
		}
	}

	// map vertices to component ID.
	let sccs = graph.build_scc();
	let mut comp_id: Vec<usize> = vec![0; n];
	let n_comp = sccs.sccs.len();
	for c in 0..n_comp {
		for &v in sccs.sccs[c].iter() {
			comp_id[v] = c;
		}
	}

	let mut c = vec![vec![1011; n_comp]; n_comp];
	for i in 0..n {
		for j in 0..n {
			let ci = comp_id[i];
			let cj = comp_id[j];

			c[ci][cj] = min(c[ci][cj], d[i][j]);
		}
	}

	// Floyd on new graph.
	for k in 0..n_comp {
		for i in 0..n_comp {
			for j in 0..n_comp {
				c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
			}
		}
	}

	// Compute final result
	let mut r: i64 = 0;
	for i in 0..n {
		for j in 0..n {
			let ci = comp_id[i];
			let cj = comp_id[j];
			r = (r * 16807 + c[ci][cj] as i64) % 2147483647;
		}
	}
	writeln!(writer, "{}", r).ok();
}
