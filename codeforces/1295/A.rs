/// Scanner class
/// Copied from https://codeforces.com/contest/1168/submission/54903799
///
/// Usage:
/// ```
/// let mut scanner = Scanner::default();
/// let n = scan.next::<i32>();
/// ```
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

	let ntest = scanner.next::<usize>();
	for _ in 0..ntest {
		let mut n = scanner.next::<usize>();
		if n % 2 == 1 {
			print!("{}", 7);
			n = n - 3;
		}
		for _ in 0..n/2 {
			print!("{}", 1);
		}
		println!();
	}
}
