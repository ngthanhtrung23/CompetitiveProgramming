
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(12);
	ll n; cin >> n;
	ll x[4] = {2,3,5,7};
	ll res = 0;
	REP(mask,1<<4) {
		ll prod = 1;
		REP(i,4) if ((mask >> i) & 1) {
			prod *= x[i];
		}
		if (__builtin_popcount(mask) % 2 == 0) res += n / prod;
		else res -= n / prod;
	}
	cout << res << endl;
}
