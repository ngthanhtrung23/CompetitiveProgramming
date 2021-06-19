// [1 2 3]
//
// [1]
// -> [2]
//
// [1, 2]
// -> [3, 2]
// -> [3, 5]
//
//
// [1, 2, 3]
//
// [4, 2, 3]
// [4, 6, 3]
// [4, 6, 9]
//
// max = 3
// i = 1 -> +max
// i = 2 -> +max + a[1]
// i = 3 -> +max + a[1] + a[2]
// ..
// i = k -> +max + a[1] + ... + a[k - 1]
//
// SUM = sum + max*k + s[1] + s[2] + ... + s[k - 1]

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

const int MN = 200111;
int a[MN], s[MN], sum_s[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    int n; cin >> n;
    FOR(i,1,n) {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
        sum_s[i] = sum_s[i-1] + s[i];
    }

    int max_val = a[1];
    FOR(i,1,n) {
        max_val = max(max_val, a[i]);

        cout << s[i] + max_val * i + sum_s[i - 1] << '\n';
    }
    return 0;
}
