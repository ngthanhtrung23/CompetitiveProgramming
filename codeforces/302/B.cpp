#include <iostream>
using namespace std;

int sum[100111];

int main() {
	ios :: sync_with_stdio(false);
	int n, q;
	while (cin >> n >> q) {
		for(int i = 1; i <= n; ++i) {
			int c, t; cin >> c >> t;
			sum[i] = sum[i-1] + c * t;
		}
		while (q--) {
			int t; cin >> t;
			int l = 1, r = n, res = n;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (sum[mid] >= t) {
					res = mid;
					r = mid - 1;
				}
				else l = mid + 1;
			}
			cout << res << endl;
		}
	}
}
