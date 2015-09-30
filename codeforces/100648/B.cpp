
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int c[111][111], n;
int f[TWO(12)][12];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n && n) {
        ++n;
        REP(i,n) REP(j,n) cin >> c[i][j];
        REP(k,n) REP(i,n) REP(j,n) c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

        REP(mask,TWO(n)) REP(i,n) f[mask][i] = 1000111000;
        f[1][0] = 0;
        FOR(mask,1,TWO(n)-1) REP(last,n) if (CONTAIN(mask,last)) {
            REP(next,n) if (!CONTAIN(mask,next)) {
                f[mask | TWO(next)][next] = min(f[mask | TWO(next)][next], f[mask][last] + c[last][next]);
            }
        }
        int res = 1e9 + 9;
        REP(last,n) res = min(res, f[TWO(n)-1][last] + c[last][0]);
        cout << res << endl;
    }
}

