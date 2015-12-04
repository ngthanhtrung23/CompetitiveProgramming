
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const ll INF = 1e16;
ll f[155][155], g[155][155];
ll r[155], s[155];

int main() {
    ios :: sync_with_stdio(0);
    int A, B, n;
    while (cin >> n >> A >> B) {
        int sumAll = 0;
        FOR(i,1,n) {
            cin >> r[i] >> s[i];
            sumAll += s[i];
        }

        // can not go to these states
        FOR(i,0,150) {
            f[n+1][i] = g[n+1][i] = INF;
        }
        // if eat nothing, then no need for skipping
        f[n+1][0] = g[n+1][0] = -INF;

        FORD(i,n,1) {
            FOR(S,0,150) {
                // 1st player
                f[i][S] = INF;
                // eat
                f[i][S] = min(f[i][S], g[i+1][max(0ll, S - s[i])] - r[i]);
                // pass
                f[i][S] = min(f[i][S], max(1LL, f[i+1][S] + r[i] + 1));

                // 2nd player
                g[i][S] = -INF;
                // eat
                g[i][S] = max(g[i][S], f[i+1][S] + r[i]);
                // pass
                g[i][S] = max(g[i][S], min(0LL, g[i+1][max(0ll, S - s[i])] - r[i] - 1));
            }
        }

        int res = 0;
        FOR(i,0,150)
            if (f[1][i] <= A - B) res = i;

        cout << res << ' ' << sumAll - res << endl;
    }
}
