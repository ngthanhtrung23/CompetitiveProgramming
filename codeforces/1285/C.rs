use std::cmp::{min, max};

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

/// Returns gcd(m, n).
/// gcd(0, 0) = 0
/// gcd(x, 0) = x
/// gcd(0, x) = x
fn gcd(mut m: i64, mut n: i64) -> i64 {
	while n != 0 {
		m %= n;
		std::mem::swap(&mut m, &mut n);
	}
	return m.abs();
}

/// Returns lcm(m, n).
fn lcm(m: i64, n: i64) -> i64 {
	return m / gcd(m, n) * n;
}

fn main() {
	let mut scanner = Scanner::default();
	assert_eq!(gcd(0, 0), 0);
	assert_eq!(gcd(0, 10), 10);
	assert_eq!(gcd(10, 0), 10);

	let x = scanner.next::<i64>();
	let mut res = x;  // (x, 1)
	let mut save_min = 1;

	for a in 1..(1000 * 1000 + 1) {
		if x % a == 0 {
			let b = x / a;
			if lcm(a, b) == x {
				if max(a, b) < res {
					res = max(a, b);
					save_min = min(a, b);
				}
			}
		}
	}

	println!("{} {}", res, save_min);
}
