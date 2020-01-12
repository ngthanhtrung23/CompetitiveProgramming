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

fn main() {
	let mut scanner = Scanner::default();

	let n_query = scanner.next::<u32>();
	for _ in 0..n_query {
		let n = scanner.next::<usize>();
		let a: Vec<i64> = (0..n).map(|_| scanner.next()).collect();

		let sum_all = a.iter().sum();
		let prefix_sum:Vec<i64> = a.iter().scan(0, |sum, &x| { *sum += x; Some(*sum) }).collect::<Vec<_>>();

		let mut max_subarr_sum:i64 = a[0];
		let mut min_prefix_sum:i64 = 0;
		for i in 0..n-1 {
			let cur_sum = prefix_sum[i];
			max_subarr_sum = max(max_subarr_sum, cur_sum - min_prefix_sum);
			min_prefix_sum = min(min_prefix_sum, cur_sum);
		}

		let mut min_prefix_sum:i64 = a[0];
		for i in 1..n {
			let cur_sum = prefix_sum[i];
			max_subarr_sum = max(max_subarr_sum, cur_sum - min_prefix_sum);
			min_prefix_sum = min(min_prefix_sum, cur_sum);
		}

		if max_subarr_sum < sum_all {
			println!("YES");
		} else {
			println!("NO");
		}
	}
}
