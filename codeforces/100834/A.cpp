
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

bool allSame(const string& s) {
	for(char c : s) if (c != s[0]) return false;
	return true;
}

struct Str {
	string x;
	int rep;
	ll len;
	bool all;
	ll firstEqual, lastEqual;

	friend istream& operator >> (istream& cin, Str& a) {
		cin >> a.x >> a.rep;

		a.len = SZ(a.x) * a.rep;
		if (allSame(a.x)) {
			a.all = true;
			a.firstEqual = a.lastEqual = -1;
		}
		else {
			a.all = false;
			a.firstEqual = 1;
			while (a.x[ a.firstEqual ] == a.x[0]) ++a.firstEqual;
			a.lastEqual = 1;
			while (a.x[ SZ(a.x) - a.lastEqual - 1 ] == a.x.back()) ++a.lastEqual;
		}
		return cin;
	}
} a[MN];

vector<int> ke[MN];
int n;
pair<ll,int> res;

int digit(char c) {
	return - (c - '0');
}

void update(int u, pair<ll,int>& cur) {
	if (a[u].all) {
		if (digit(a[u].x[0]) == cur.second) {
			cur.first += a[u].len;
		}
		else {
			cur.first = a[u].len;
			cur.second = digit(a[u].x[0]);
		}
	}
	else {
		if (digit(a[u].x[0]) == cur.second) {
			cur.first += a[u].firstEqual;
			res = max(res, cur);
		}
		cur.first = a[u].lastEqual;
		cur.second = digit(a[u].x.back());
	}
}

void dfs(int u, int fu, pair<ll,int>& cur) {
	// add a[u]
	update(u, cur);
	res = max(res, cur);

	for(int v : ke[u]) {
		if (v == fu) continue;
		dfs(v, u, cur);

		// add a[u]
		update(u, cur);
		res = max(res, cur);
	}
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n) {
		res = make_pair(0, 0);
		FOR(i,1,n) {
			cin >> a[i];

			if (a[i].all) res = max(res, make_pair(a[i].len, digit(a[i].x[0])));
			else {
				int cur = -1, len = 0;
				for(char c : a[i].x) {
					int u = c - '0';
					if (u == cur) ++len;
					else len = 1, cur = u;

					res = max(res, make_pair((ll) len, -u));
				}
				if (a[i].rep > 1) {
					if (a[i].x[0] == a[i].x.back()) {
						res = max(res, make_pair(a[i].firstEqual + a[i].lastEqual, digit(a[i].x[0])));
					}
				}
			}
		}
		FOR(i,1,n) ke[i].clear();
		FOR(i,2,n) {
			int u, v; cin >> u >> v;
			ke[u].push_back(v);
			ke[v].push_back(u);
		}
		pair<ll,int> cur = make_pair(0LL, 99);
		dfs(1, -1, cur);
		cout << -res.second << ' ' << res.first << endl;
	}
}
