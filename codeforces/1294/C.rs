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

fn solve(mut n:i32) {
	let mut a = -1;
	let mut i = 2;
	while i * i <= n {
		if n % i == 0 {
			n /= i;
			if a < 0 {
				a = i;
			} else {
				let b = i;
				if n > b {
					println!("YES");
					println!("{} {} {}", a, b, n);
				} else {
					println!("NO");
				}
				return;
			}
		}
		i += 1;
	}
	println!("NO");
}

fn main() {
	let mut scanner = Scanner::default();
	let ntest = scanner.next::<usize>();
	for _ in 0..ntest {
		let n = scanner.next::<i32>();
		solve(n);
	}
}
