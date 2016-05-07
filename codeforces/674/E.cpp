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

double safe_sqrt(double x) {
    return sqrt(max((double) 0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 500111;
const int MAX = 40;
double f[MN][MAX + 5], newf[MN][MAX+5];
int father[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(3);

    int q;
    while (scanf("%d", &q) == 1) {
        memset(father, 0, sizeof father);
        memset(f, 0.0, sizeof f);
        REP(i,MAX) f[1][i] = 1.0;

        int n = 1;
        FOR(i,1,q) {
            int typ; scanf("%d", &typ);
            int u; scanf("%d", &u);

            if (typ == 1) {
                ++n;
                father[n] = u;
                REP(i,MAX) f[n][i] = 1.0;

                int v;
                v = n; u = father[n];
                // calculate newf
                REP(up,MAX) {
                    FOR(h,up,MAX) {
                        newf[u][h] = f[u][h];
                        if (v == n) {
                            if (h == 0) newf[u][h] *= 0.5;
                            else newf[u][h] *= 0.5 * (1 + f[v][h-1]);
                        }
                        else {
                            if (h == 0) {
                            } else {
                                newf[u][h] /= 0.5 * (1 + f[v][h-1]);
                                newf[u][h] *= 0.5 * (1 + newf[v][h-1]);
                            }
                        }
                    }
                    v = u;
                    u = father[u];
                    if (!u) break;
                }
                // update f
                v = n; u = father[n];
                REP(up,MAX) {
                    REP(h,MAX) {
                        f[u][h] = newf[u][h];
                    }
                    v = u;
                    u = father[u];
                    if (!u) break;
                }
            }
            else {
                double last = 0.0;
                double res = 0.0;
                REP(h,MAX) {
                    res += h * (f[u][h] - last);
                    last = f[u][h];
                }
                printf("%.9f\n", (double) res);
            }
        }
    }
}
