#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 2011;
const int MOD = 1e9 + 7;
int n, a[MN], b[MN], eq[MN][MN], f[MN][MN], g[MN], dp[MN][MN];

void init() {
    FOR(i,0,MN-1) FOR(j,0,MN-1) {
        if (i == 0 && j == 0) dp[i][j] = 1;
        else if (i < j) dp[i][j] = 0;
        else {
            if (i) dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            if (j) dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
        }
    }
    FOR(i,0,MN-1) g[i] = dp[i][i];
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    init();

    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,n) scanf("%d", &b[i]);

        FOR(i,1,n) FOR(j,1,n) {
            eq[i][j] = (a[i] == b[j]) ? eq[i-1][j-1] + 1 : 0;
        }

        memset(f, 0, sizeof f);
        FOR(i,0,n) f[i][0] = f[0][i] = 1;

        FOR(i,1,n) FOR(j,1,n) {
            if (a[i] != b[j]) {
                f[i][j] = (f[i-1][j] + f[i][j-1]) % MOD;
            }
            else {
                int u = eq[i][j];

                if (i == u && j == u) 
                    f[i][j] = f[i-u][j-u] * (ll) g[u] % MOD;

                FOR(k,0,u) {
                    if (j > u)
                        f[i][j] = (f[i][j] + f[i-k][j-u-1] * (ll) dp[u][k]) % MOD;

                    if (i > u)
                        f[i][j] = (f[i][j] + f[i-u-1][j-k] * (ll) dp[u][k]) % MOD;
                }
            }
        }

        cout << f[n][n] << endl;
    }
}
