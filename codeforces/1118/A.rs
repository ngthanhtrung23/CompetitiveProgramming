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

	let n_query = scanner.next::<usize>();
	for _ in 0..n_query {
		let vol = scanner.next::<i64>();
		let price_1 = scanner.next::<i64>();
		let price_2 = scanner.next::<i64>();

		let solve = |vol, price_1, price_2| {
			if price_2 >= price_1 * 2 {
				return vol * price_1;
			}
			return (vol / 2) * price_2 + (vol % 2) * price_1;
		};

		println!("{}", solve(vol, price_1, price_2));
	}
}
