use std::collections::{HashMap, HashSet};

#[derive(Default)]
struct Scanner {
	buffer: Vec<String>
}
impl Scanner {
	fn next<T: std::str::FromStr>(&mut self) -> T {
		loop {
			if let Some(token) = self.buffer.pop() {
				return token.parse().ok().expect("Failed parsing input")
			}
			let mut input = String::new();
			std::io::stdin().read_line(&mut input).expect("Failed reading input");
			self.buffer = input.split_whitespace().rev().map(String::from).collect();
		}
	}
}

fn main() {
	let mut scanner = Scanner::default();
	// read names.
	let mut id_of: HashMap<(String, String), i32> = HashMap::new();
	let mut n_id = 0;
	loop {
		let a1 = scanner.next::<String>();
		if a1.starts_with('-') {
			break;
		}

		let a2 = scanner.next::<String>();
		let b1 = scanner.next::<String>();
		let b2 = scanner.next::<String>();

		id_of.insert((a1, a2), n_id);
		id_of.insert((b1, b2), n_id);
		n_id += 1;
	}

	// Answer queries.
	let mut all: HashSet<i32> = HashSet::new();
	loop {
		let query = scanner.next::<String>();
		match query.as_str() {
			"END" => {
				break;
			}
			"+" => {
				let q1 = scanner.next::<String>();
				let q2 = scanner.next::<String>();
				if let Some(&id) = id_of.get(&(q1, q2)) {
					all.insert(id);
				}
			}
			"-" => {
				let q1 = scanner.next::<String>();
				let q2 = scanner.next::<String>();
				if let Some(id) = id_of.get(&(q1, q2)) {
					all.remove(id);
				}
			}
			"FIND" => {
				let q1 = scanner.next::<String>();
				let q2 = scanner.next::<String>();
				if let Some(id) = id_of.get(&(q1, q2)) {
					if all.contains(id) {
						println!("FOUND");
					} else {
						println!("404");
					}
				}
			}
			"UNION" => {
				println!("{}", all.len());
			}
			_ => {
				eprintln!("Unknown query {}", query);
			}
		}
	}
}
