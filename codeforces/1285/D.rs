use std::cmp::{max, min};

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

fn get_bit(x: i32, bit: i32) -> i32 {
	return (x >> bit) & 1;
}

fn solve(bit: i32, a: Vec<i32>) -> i32 {
	if bit < 0 {
		return 0;
	}

	let on_bit:Vec<i32> = a.iter().clone().filter(|&&x| get_bit(x, bit) == 1).map(|x| *x).collect();
	let off_bit:Vec<i32> = a.iter().clone().filter(|&&x| get_bit(x, bit) == 0).map(|x| *x).collect();
	if on_bit.is_empty() {
		return solve(bit - 1, off_bit);
	}
	if off_bit.is_empty() {
		return solve(bit - 1, on_bit);
	}

	let f_on = solve(bit - 1, on_bit);
	let f_off = solve(bit - 1, off_bit);

	return min(
		max((1<<bit) + f_on, f_off),
		max(f_on, (1<<bit) + f_off)
	)
}

fn main() {
	let mut scanner = Scanner::default();
	let n = scanner.next::<usize>();
	let a:Vec<i32> = (0..n).map(|_| scanner.next()).collect();

	println!("{}", solve(29, a));
}
