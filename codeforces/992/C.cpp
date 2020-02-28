
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()

const int MOD = 1e9 + 7;
long long power(long long x, long long k) {
    long long res = 1;
    while (k) {
        if (k & 1) res = res * x % MOD;
        k >>= 1;
        x = x * x % MOD;
    }
    return res % MOD;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    // kho qua' :(
    int x, k; cin >> x >> k;
    if (x == 0) {
        cout << 0 << endl;
        return 0;
    }
    x %= MOD;
    long long res = (power(2, k + 1) * x % MOD - (power(2, k) % MOD- 1) + MOD) % MOD + MOD;
    cout << res % MOD << endl;
    return 0;
}
