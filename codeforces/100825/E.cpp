
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 111;
int n, m, s, t;
int c[MN][MN];
long long f[MN], g[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m >> s >> t) {
        ++s;
        memset(c, 0, sizeof c);
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ++u; ++v;
            c[u][v] = c[v][u] = 1;
        }
        memset(f, 0, sizeof f);
        f[s] = 1;
        FOR(turn,1,t) {
            memset(g, 0, sizeof g);
            FOR(i,1,n) FOR(j,1,n) if (c[i][j]) g[i] += f[j];

            FOR(i,1,n) f[i] = g[i];
        }
        ll res = 0;
        FOR(i,1,n) res += f[i];
        cout << res << endl;
    }
}
