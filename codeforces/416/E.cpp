#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 511;
const int MM = MN * MN;
const int oo = 1000111000;

int n, m, eu[MM], ev[MM], ec[MM];
int c[MN][MN], f[MN][MN];
int res[MN][MN], cnt[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        FOR(i,1,n) FOR(j,1,n) c[i][j] = oo;
        FOR(i,1,n) c[i][i] = 0;
        
        FOR(i,1,m) {
            cin >> eu[i] >> ev[i] >> ec[i];
            c[eu[i]][ev[i]] = min(c[eu[i]][ev[i]], ec[i]);
            c[ev[i]][eu[i]] = c[eu[i]][ev[i]];
        }

        FOR(i,1,n) FOR(j,1,n) f[i][j] = c[i][j];
        FOR(k,1,n)
            FOR(i,1,n)
            FOR(j,1,n)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);

        memset(res, 0, sizeof res);
        FOR(start,1,n) {
            FOR(u,1,n)
                if (u == start) cnt[u] = 0;
                else {
                    cnt[u] = 0;
                    FOR(v,1,n) if (u != v && f[start][u] == f[start][v] + c[v][u])
                        ++cnt[u];
                }

            FOR(target,1,n)
                FOR(u,1,n)
                    if (f[start][u] + f[u][target] == f[start][target])
                        res[start][target] += cnt[u];
        }

        FOR(i,1,n) FOR(j,i+1,n) if (f[i][j] == oo) res[i][j] = 0;
        FOR(i,1,n) FOR(j,i+1,n) cout << res[i][j] << ' '; cout << endl;
    }
    return 0;
}

