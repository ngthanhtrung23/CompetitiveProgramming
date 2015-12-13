
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

const int MN = 11;
int c[MN], n, a;
int tru[100111], trc[100111];

void trace(int u) {
	if (u == a) return ;

	trace(tru[u]);
	cout << trc[u];
}

void solve() {
	queue<int> qu;
	FOR(i,1,n) if (c[i] > 0) {
		int u = c[i] % a;
		qu.push(u);
		tru[u] = a;
		trc[u] = c[i];
	}

	while (!qu.empty()) {
		int u = qu.front(); qu.pop();
		if (u == 0) {
			trace(u);
			cout << endl;
			return ;
		}
		FOR(i,1,n) {
			int v = (u * 10 + c[i]) % a;
			if (tru[v] < 0) {
				qu.push(v);
				tru[v] = u;
				trc[v] = c[i];
			}
		}
	}
	cout << -1 << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n) {
		FOR(i,1,n) cin >> c[i];
		sort(c+1, c+n+1);
		cin >> a;

		memset(tru, -1, sizeof tru);
		memset(trc, -1, sizeof trc);

		solve();
	}
}
