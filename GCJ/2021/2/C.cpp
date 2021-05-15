#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MN = 100111;
const int MOD = 1e9 + 7;

int a[MN], n;
vector<int> idOf[MN];

int fact[MN], inv_fact[MN];

int power(int x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    int mid = power(x, k / 2);
    mid = mid * mid % MOD;

    if (k % 2) return mid * x % MOD;
    return mid;
}

void init() {
    cin >> n;
    FOR(i,1,n) {
        idOf[i].clear();
        idOf[i].push_back(0);
    }

    FOR(i,1,n) {
        cin >> a[i];
        idOf[a[i]].push_back(i);
    }

    FOR(i,1,n) idOf[i].push_back(n+1);

    /*
    FOR(i,1,n) {
        PR0(idOf[i], SZ(idOf[i]));
    }
    */
}

int C(int n, int k) {
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int solve(int l, int r, int valMax) {
    if (l > r) return 1;

    auto it = upper_bound(idOf[valMax].begin(), idOf[valMax].end(), r);
    assert(it != idOf[valMax].begin());
    --it;
    int i = *it;

    if (i > r) return 0;
    if (i < l) return 0;

    return C(r - l, i - l)
        * solve(l, i - 1, valMax) % MOD
        * solve(i + 1, r, valMax + 1) % MOD;
}

int32_t main() {
    ios::sync_with_stdio(0);

    fact[0] = 1;
    FOR(i,1,100000) {
        fact[i] = fact[i-1] * i % MOD;
    }

    FOR(i,0,100000) {
        inv_fact[i] = power(fact[i], MOD - 2);
        assert(fact[i] * inv_fact[i] % MOD == 1);
    }

    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        init();
        int res = solve(1, n, 1);
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}
