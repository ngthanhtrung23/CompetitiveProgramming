
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

int n, a[MN], pos[MN], f[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (cin >> n) {
		FOR(i,1,n) {
			cin >> a[i];
			pos[a[i]] = i;
		}
		int res = 0;
		FORD(i,n,1) {
			f[i] = 1;
			if (i < n && pos[i+1] > pos[i]) f[i] = f[i+1] + 1;
			res = max(res, f[i]);
		}
		cout << n - res << endl;
	}
}
