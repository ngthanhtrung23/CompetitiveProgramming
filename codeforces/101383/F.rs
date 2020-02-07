use std::io;
use std::str;
use io::Write;
use std::ops::{Add, Mul, AddAssign};

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

#[derive(Clone, Copy)]
struct Modular {
	x: i64,
}

const MOD:i64 = 1_000_000_007;
impl Modular {
	pub fn new(x: i64) -> Self {
		Self {
			x: x % MOD,
		}
	}
}

impl Add for Modular {
	type Output = Modular;

	fn add(self, rhs: Modular) -> Self::Output {
		let mut tmp = self.x + rhs.x;
		if tmp >= MOD {
			tmp -= MOD;
		}
		return Modular::new(tmp);
	}
}
impl AddAssign for Modular {
	fn add_assign(&mut self, rhs: Self) {
		self.x += rhs.x;
		if self.x >= MOD {
			self.x -= MOD;
		}
	}
}
impl Mul for Modular {
	type Output = Modular;

	fn mul(self, rhs: Modular) -> Self::Output {
		return Modular::new((self.x * rhs.x) % MOD);
	}
}

fn main() {
	let mut scanner = scanner_from_file("meganim.in");
	let mut writer = writer_to_file("meganim.out");
	let n = scanner.next::<usize>();
	let limit_i64 = scanner.next::<i64>() + 1;

	let bits: Vec<u8> = format!("0{:b}", limit_i64).into_bytes().iter().map(|x| x - 48).collect();
	let mut c = vec![vec![Modular::new(0); n+1]; n+1];
	for i in 0..n+1 {
		c[i][0] = Modular::new(1);
		for j in 1..i+1 {
			c[i][j] = c[i-1][j-1] + c[i-1][j];
		}
	}

	// g[i][val] = how many ways of setting i bits, so that the xor-sum is equal to val.
	let mut g = vec![vec![Modular::new(0); 2]; n+1];
	g[0][0] = Modular::new(1);
	for i in 1..n+1 {
		g[i][0] = g[i-1][0] + g[i-1][1];
		g[i][1] = g[i][0];
	}

	// f[i][j] = how many ways to make sum xor of first i bits equal to 0,
	//           with exactly `j` number less than `limit`
	let mut f = vec![vec![Modular::new(0); n + 1]; bits.len()];
	f[0][0] = Modular::new(1);
	for pos in 0..bits.len()-1 {
		for less in 0..n+1 {
			let equal = n - less;
			let bound = if bits[pos+1] == 0 { 0 } else { equal };
			for equal_to_less in 0..bound+1 {
				let stay_equal = equal - equal_to_less;
				let cur_sum = stay_equal * (bits[pos + 1] as usize) % 2;

				let x = f[pos][less] * c[equal][equal_to_less] * g[less][cur_sum];
				f[pos + 1][less + equal_to_less] += x;
			}
		}
	}
	writeln!(writer, "{}", f[bits.len()-1][n].x).ok();
}
