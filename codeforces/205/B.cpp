#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios :: sync_with_stdio(false);
	
	int n;
	while (cin >> n) {
		long long res = 0, added = 0, a, last = 0;
		for(int i = 1; i <= n; ++i) {
			cin >> a; a += added;
			if (a < last) {
				added += last - a;
				res += last - a;
				a = last;
			}
			last = a;
		}
		cout << res << endl;
	}
	return 0;
}