#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
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

int f[2][1000111];
const int INF = 1000111000111LL;

int32_t main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n) {
        string s; cin >> s;
        s = " " + s + " ";

        if (s[1] == 'a') {
            f[0][1] = 0;
            f[1][1] = -INF;
        } else if (s[1] == 'b') {
            f[1][1] = 0;
            f[0][1] = -INF;
        } else {
            assert(s[1] == '?');
            f[0][1] = f[1][1] = 0;
        }

        FOR(i,2,n) {
            if (s[i] == 'a') {
                f[0][i] = max(f[0][i-1], f[1][i-1] - 1);
                f[1][i] = -INF;
            } else if (s[i] == 'b') {
                f[1][i] = max(f[0][i-1] + 1, f[1][i-1]);
                f[0][i] = -INF;
            } else {
                assert(s[i] == '?');
                f[0][i] = max(f[0][i-1], f[1][i-1] - 1);
                f[1][i] = max(f[0][i-1] + 1, f[1][i-1]);
            }
        }
        cout << max(f[0][n], f[1][n]) << endl;
    }
    return 0;
}
