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

const int MN = 1011;

int a[MN], b[MN];
int f[MN][10111];

template<typename T>
void upMin(T& ff, T val) {
    if (val < ff) ff = val;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n; cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) cin >> b[i];

    memset(f, 0x3f, sizeof f);
    int INF = f[0][0];

    f[1][0] = b[1];
    FOR(i,1,n) FOR(t,0,10000) {
        if (f[i][t] == INF) continue;

        // B read i+1
        if (i+1 <= n) {
            int ta = max(
                f[i][t] + a[i],     // a finish i
                t + b[i] + b[i+1]   // b finish i+1
            );
            upMin(f[i+1][t + b[i]], ta);
        }

        // B read i+2
        if (i+2 <= n) {
            int ta = max(
                f[i][t] + a[i] + a[i+1],  // a finish i & i+1
                t + b[i] + b[i+2]         // b finish i+2
            );
            upMin(f[i+2][t + b[i]], ta);
        }
    }

    int res = INF;
    FOR(t,0,10000) {
        if (f[n][t] == INF) continue;

        int ta = f[n][t] + a[n];
        int tb = t + b[n];

        res = min(res, max(ta, tb));
    }
    cout << res << endl;

    return 0;
}

