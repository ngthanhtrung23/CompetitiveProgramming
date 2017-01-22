
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 5011;
const int MOD = 1e9 + 7;

#define next acjalscjl

int a[MN];
int cur[33];
int next[MN];
int f[2][MN], g[2][MN];


inline int add(int a, int b) {
    int res = a + b;
    if (res >= MOD) res -= MOD;
    return res;
}
inline int sub(int a, int b) {
    int res = a - b;
    if (res < 0) res += MOD;
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        string s; cin >> s;
        FOR(i,1,n) a[i] = s[i-1] - 'a' + 1;

        memset(cur, 0, sizeof cur);
        FOR(i,1,n) {
            FOR(c,1,30) next[i] = cur[a[i]];
            cur[a[i]] = i;
        }

        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);

        FOR(j,1,n) {
            f[1][j] = 1;

            g[1][j] = sub(add(f[1][j], g[1][j-1]), f[1][next[j]]);
        }

        FOR(i,2,n) {
            int t = i % 2;
            memset(f[t], 0, sizeof f[t]);
            memset(g[t], 0, sizeof g[t]);

            FOR(j,1,n) {
                f[t][j] = g[1-t][j];
                g[t][j] = sub(add(g[t][j-1], f[t][j]), f[t][next[j]]);
            }
        }

        int res = g[n%2][n];
        cout << res << '\n';
    }
}
