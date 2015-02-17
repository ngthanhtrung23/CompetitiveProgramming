
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

double f[TWO(18)];
double a[22][22];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        REP(i,n) REP(j,n) cin >> a[i][j];
        memset(f, 0, sizeof f);
        f[TWO(n) - 1] = 1.0;

        FORD(mask,TWO(n)-1,1) if (f[mask] > 1e-100) {
            int cnt = __builtin_popcount(mask);
            int choices = cnt * (cnt - 1) / 2;
            REP(u,n) if (CONTAIN(mask,u))
                REP(v,n) if (CONTAIN(mask,v) && u != v) {
                    f[mask - TWO(v)] += f[mask] * a[u][v] / choices;
                }
        }
        REP(i,n) cout << f[TWO(i)] << ' '; cout << endl;
    }
    return 0;
}
