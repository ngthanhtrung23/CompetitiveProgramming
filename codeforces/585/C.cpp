#include<bits/stdc++.h>

using namespace std;

long long gcd(long long x, long long y) {
	if (x < y) return gcd(y, x);
	if (x % y == 0) return y;
	return gcd(y, x % y);
}

int main() {
	long long x, y, q;
	cin >> x >> y;
	
	if (gcd(x, y) != 1) {
		cout << "Impossible" << endl;
	} else {
		while (x > 1 && y > 1) {
			if (x > y) {
				q = x / y;
				x = x % y;
				cout << q << "A";
			} else {
				q = y / x;
				y = y % x;
				cout << q << "B";
			}
		}
		
		if (x > 1) {
			cout << (x - 1) << "A";
		}
		
		if (y > 1) {
			cout << (y - 1) << "B";
		}
		
		cout << endl;
	}
}