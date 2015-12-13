
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
string a, a_rev;
int l;
ll p[MN], h[2][MN];

ll get(int t, int u) {
	ll res = 0;
	for(int x = u; x > 0; x -= x & -x)
		res += h[t][x];
	return res;
}

void update(int t, int u, ll val) {
	for(int x = u; x < MN; x += x & -x)
		h[t][x] += val;
}

ll getHash(int u, int v) {
	return (get(0, v) - get(0, u-1)) * p[100000 - u];
}
ll getHashRev(int u, int v) {
	return (get(1, v) - get(1, u-1)) * p[100000 - (l - v + 1)];
}

int value(char c) {
	return c - 'a' + 1;
}

bool isPalin(int l, int r) {
	return getHash(l, r) == getHashRev(l, r);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	p[0] = 1; FOR(i,1,MN-1) p[i] = p[i-1] * 31;
	while (cin >> a) {
		l = a.length();
		a = " " + a + " ";

		memset(h, 0, sizeof h);
		FOR(i,1,l) {
			update(0, i, value(a[i]) * p[i]);
			update(1, i, value(a[i]) * p[l-i+1]);
		}

		int q; cin >> q;
		while (q--) {
			int typ; cin >> typ;
			if (typ == 1) {
				int u, v; cin >> u >> v;
				cout << (isPalin(u, v) ? "YES" : "NO") << '\n';
			}
			else {
				int u; char c; cin >> u >> c;
				update(0, u, -value(a[u]) * p[u]);
				update(1, u, -value(a[u]) * p[l-u+1]);

				a[u] = c;

				update(0, u, value(a[u]) * p[u]);
				update(1, u, value(a[u]) * p[l-u+1]);
			}
		}
		cout << '\n';
	}
}
