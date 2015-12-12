
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

const ll MOD = 1e9 + 7;
const int MN = 1000111;

int n, m, k;
ll inv[MN], C[MN], gt[MN], inv_gt[MN];

ll power(ll x, ll k) {
	if (k == 0) return 1;
	if (k == 1) return x % MOD;
	ll mid = power(x, k >> 1);
	mid = mid * mid % MOD;

	if (k & 1) return mid * x % MOD;
	return mid;
}

ll f(int k) {
	if (k <= 0) return 0;
	return k * power(k-1, n-1) % MOD;
}

ll Cnk(int n, int k) {
	if (n < 0 || k < 0 || n < k) return 0;
	return gt[n] * inv_gt[k] % MOD * inv_gt[n-k] % MOD;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	REP(i,MN) inv[i] = power(i, MOD - 2);
	REP(i,MN) {
		if (i == 0) gt[i] = 1;
		else gt[i] = gt[i-1] * i % MOD;

		inv_gt[i] = power(gt[i], MOD - 2);
	}

	int ntest; cin >> ntest;
	FOR(test,1,ntest) {
		cin >> n >> m >> k;
		FOR(i,0,k) {
			if (i == 0) C[i] = 1;
			else C[i] = C[i-1] * (m - i + 1LL) % MOD * inv[i] % MOD;
		}
		ll res = 0;
		FOR(i,0,k) {
			ll cur = f(i);
			cur = cur * Cnk(k, i) % MOD;
			if ((k - i) & 1) res = (res - cur + MOD) % MOD;
			else res = (res + cur) % MOD;
		}
		res = (res * C[k]) % MOD;
		cout << "Case #" << test << ": " << res << endl;
	}
}
