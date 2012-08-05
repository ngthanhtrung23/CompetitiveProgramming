#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n, ind[11], m, res, save;
string a[11], b[22];

void update(int q) {
	int start = 0;
	for(int i = 1; i <= n; i++) {
		while (start <= m && b[start] != a[ind[i]]) ++start;
		if (start > m) return ;
		++start;
	}
	int cur = n * (n-1) / 2 + 1;
	for(int i = 1; i <= n; i++)
		for(int j = i+1; j <= n; j++)
			if (ind[i] > ind[j]) --cur;
	if (cur > res) {
		res = cur;
		save = q;
	}
}

int main() {
	ios :: sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int q; cin >> q;
	res = -1;

	for(int qq = 1; qq <= q; ++qq) {
		cin >> m;
		for(int i = 1; i <= m; i++) cin >> b[i];
		for(int i = 1; i <= n; i++) ind[i] = i;

		do {
			update(qq);
		} while (next_permutation(ind+1, ind+n+1));

	}

	if (res < 0) puts("Brand new problem!");
	else {
		cout << save << endl;
		cout << "[:";
		while (res--) cout << '|';
		cout << ":]" << endl;
	}
	return 0;
}
