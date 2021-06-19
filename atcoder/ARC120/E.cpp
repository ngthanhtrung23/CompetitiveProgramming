// 0 2 4 6 8
//
// A(i) = 8
// A(j) = 6
// A(j-1) = 4
//
//
// 0 2 4 6 8  92 94 96 98 100
//
// f(i) = min(  max(f(j), (A(i) - A(j-1)) / 2)  for 1 < j < i)

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
int a[MN], f[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        FOR(i,1,n) {
            f[i] = a[i] - a[1];

            int max_j = (i == n) ? (i - 1) : (i-2);
            int min_j = max(i - 10, 2LL);

            FOR(j,min_j,max_j) {
                f[i] = min(f[i],
                        max(f[j], a[i] - a[j-1]));
            }
        }

        cout << f[n] / 2 << endl;
    }
    return 0;
}
