#include <bits/stdc++.h>
using namespace std;

int cnt[1011];

int main() {
	int n;
	while (cin >> n) {
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < n; ++i) {
			int a; cin >> a;
			cnt[a] += 1;
		}
		int res = 0;
		for(int turn = 0; turn < 1000; ++turn) {
			int has = 0;
			for(int i = 1; i <= 1000; ++i) {
				if (cnt[i] > 0) {
					cnt[i] -= 1;
					if (has) ++res;
					has = 1;
				}
			}
		}
		cout << res << endl;
	}
	return 0;
}