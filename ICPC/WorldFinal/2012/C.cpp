#include <bits/stdc++.h>
#define int long long
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

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 22;
int mask(int i) { return 1<<(i-1); }
int contains(int s, int i) { return s & mask(i); }

int n, m;
int c[22][22];
int f0[1<<18][22], fn[1<<18][22];
const int INF = 1e12;

void update(int &f, int val) {
    f = min(f, val);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int test = 0;
    while (cin >> n >> m) {
        REP(s,1<<(n-2)) REP(last,n) f0[s][last] = fn[s][last] = INF;
        REP(i,n) REP(j,n) c[i][j] = INF;
        while (m--) {
            int cc, u, v; cin >> u >> v >> cc;
            c[u][v] = min(c[u][v], cc);
            c[v][u] = c[u][v];
        }
        REP(k,n) REP(i,n) REP(j,n)
            c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

        if (n == 3) {
            cout << "Case " << ++test << ": " << c[0][1] + c[1][2] + c[2][1] + c[1][0] << '\n';
            continue;
        }

        FOR(i,1,n-2) {
            f0[mask(i)][i] = c[0][i];
            fn[mask(i)][i] = c[n-1][i];
        }
        int need = (n - 2) / 2;
        REP(s,1<<(n-2)) FOR(u,1,n-2) {
            if (__builtin_popcount(s) == need + 1) continue;

            int cur = f0[s][u];
            if (cur < INF) {
                FOR(v,1,n-2) if (!contains(s,v)) {
                    update(f0[s | mask(v)][v], cur + c[u][v]);
                }
            }

            cur = fn[s][u];
            if (cur < INF) {
                FOR(v,1,n-2) if (!contains(s,v)) {
                    update(fn[s | mask(v)][v], cur + c[u][v]);
                }
            }
        }

        int res = INF;
        REP(s1,1<<(n-2)) if (__builtin_popcount(s1) == need) {
            int s2 = (1<<(n-2)) - 1 - s1;

            FOR(u,1,n-2) if (contains(s1,u))
                FOR(v,1,n-2) if (contains(s2,v))
                FOR(x,1,n-2) if (contains(s1,x))
                FOR(y,1,n-2) if (contains(s2,y)) {
                    res = min(res,
                            f0[s1][u] + c[u][v] + fn[s2][v]
                            + fn[s1][x] + c[x][y] + f0[s2][y]
                            );
                }
        }
        cout << "Case " << ++test << ": " << res << '\n';
    }
}
