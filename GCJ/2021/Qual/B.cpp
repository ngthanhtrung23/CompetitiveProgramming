// Algo: 1D DP

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
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

int f[1011][2];
const int INF = 1000111000;

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int cj, jc; cin >> cj >> jc;
        string s; cin >> s;

        int n = SZ(s);
        s = " " + s + " ";

        // c = 0
        // j = 1
        f[1][0] = f[1][1] = INF;

        if (s[1] == '?' || s[1] == 'C') {
            f[1][0] = 0;
        }
        if (s[1] == '?' || s[1] == 'J') {
            f[1][1] = 0;
        }

        FOR(i,2,n) {
            f[i][0] = f[i][1] = INF;

            if (s[i] == '?' || s[i] == 'C') {
                f[i][0] = min(f[i-1][0], f[i-1][1] + jc);
            }
            if (s[i] == '?' || s[i] == 'J') {
                f[i][1] = min(f[i-1][1], f[i-1][0] + cj);
            }
        }

        int res = min(f[n][0], f[n][1]);
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}

