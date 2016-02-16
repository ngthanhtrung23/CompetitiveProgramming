
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

const int MN = 20;
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n;
int c[MN][MN];
ll f[TWO(MN)][MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int m;
    while (cin >> n >> m) {
        memset(c, 0, sizeof c);
        while (m--) {
            int u, v; cin >> u >> v;
            --u; --v;

            c[u][v] = c[v][u] = 1;
        }

        ll res = 0;
        FORD(N,n,1) {
            memset(f, 0, sizeof f);
            // how many cycles go through u?
            int u = N - 1;
            f[TWO(u)][u] = 1;

            REP(mask,TWO(N)) REP(last,N)
                if (f[mask][last]) {
                    REP(u,N) if (c[last][u] && !CONTAIN(mask,u)) {
                        f[mask | TWO(u)][u] += f[mask][last];
                    }
                }

            REP(mask,TWO(N)) REP(last,N) if (__builtin_popcount(mask) >= 3) {
                if (c[last][u]) res += f[mask][last];
            }
        }
        cout << res / 2 << endl;
    }
}
