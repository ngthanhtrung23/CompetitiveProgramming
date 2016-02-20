
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

ll mult(ll a, ll b) {
	return a * b % MOD;
}
ll power(ll x, ll k) {
	ll res = 1;
	while (k > 0) {
		if (k % 2) res = mult(res, x);
		x = mult(x, x);
		k >>= 1;
	}
	return res;
}
ll inverse(ll x) {
	return power(x, MOD - 2);
}

ll sub(ll a, ll b) {
	return ((a - b) % MOD + MOD) % MOD;
}

ll sum2(ll n) {
	ll cur = n;
	cur = mult(cur, n + 1);
	cur = mult(cur, 2*n+1);
	cur = mult(cur, inverse(6));
	return cur;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	ll n;
	while (cin >> n) {
		ll res = mult(mult(n, n), mult(n, n)); // n ^ 4

		ll sumg = 0;
		sumg = mult(sum2(n) + sum2(n-1), 2);
		sumg = sub(sumg, mult(n, n));

		res = sub(res, sumg);
		cout << mult(res, inverse(2)) << endl;
	}
}
