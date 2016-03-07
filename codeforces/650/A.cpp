#include <bits/stdc++.h>
#define int long long
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

const int MN = 200111;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
	int n;
	while (cin >> n) {
		map<int,int> cx, cy;
		map< pair<int,int>, int> all;
		FOR(i,1,n) {
			pair<int,int> cur;
			cin >> cur.first >> cur.second;
			cx[cur.first]++;
			cy[cur.second]++;

			all[cur]++;
		}
		ll res = 0;
		for(auto p : cx) res += p.second * (p.second - 1LL) / 2;
		for(auto p : cy) res += p.second * (p.second - 1LL) / 2;
		for(auto p : all) res -= p.second * (p.second - 1LL) / 2;
		cout << res << endl;
	}
}
