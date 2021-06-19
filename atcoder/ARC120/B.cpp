
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

int nRow, nCol;
string a[511];
char color[1011];
const int MOD = 998244353;

int32_t main() {
    ios::sync_with_stdio(0);

    while (cin >> nRow >> nCol) {
        memset(color, '.', sizeof color);

        int res = 1;
        FOR(i,1,nRow) {
            cin >> a[i];
            a[i] = " " + a[i] + " ";

            FOR(j,1,nCol) {
                if (a[i][j] != '.') {
                    if (color[i + j] != '.' && color[i + j] != a[i][j]) {
                        res = 0;
                    } else {
                        color[i + j] = a[i][j];
                    }
                }
            }
        }

        FOR(diag,2,nRow + nCol) {
            if (color[diag] == '.') {
                res = res * 2 % MOD;
            }
        }
        cout << res << endl;
    }
    return 0;
}
