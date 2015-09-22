
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n, m, k;
ll a[22], c[22][22];
ll f[TWO(18)][18];
ll res;

void update(ll& x, ll val) {
    if (x < val) {
        x = val;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> k) {
        REP(i,n) cin >> a[i];
        memset(c, 0, sizeof c);
        FOR(i,1,k) {
            int u, v; cin >> u >> v;
            --u; --v;
            cin >> c[u][v];
        }

        ll res = 0;
        memset(f, -1, sizeof f);

        REP(i,n) f[TWO(i)][i] = a[i];

        REP(mask,TWO(n)) REP(last,n) if (f[mask][last] >= 0) {
            REP(cur,n) if (!CONTAIN(mask,cur)) {
                update(f[mask | TWO(cur)][cur], f[mask][last] + a[cur] + c[last][cur]);
            }
        }
        REP(mask,TWO(n)) if (__builtin_popcount(mask) == m)
            REP(last,n)
                res = max(res, f[mask][last]);
        cout << res << endl;
    }
}
