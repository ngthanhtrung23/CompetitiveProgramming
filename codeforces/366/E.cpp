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

const int MN = 2011;
const int oo = 1000111000;

#define _(X) ((X) & (-(X)))
int a[MN][MN], bit[10][MN][MN];
int x[100111];
int has[11][11];
int m, n, k, s;

void update(int t, int u, int v, int val) {
    for(int i = u; i < MN; i += _(i))
        for(int j = v; j < MN; j += _(j))
            bit[t][i][j] = min(bit[t][i][j], val);
}

int get(int t, int u, int v) {
    int res = oo;
    for(int i = u; i > 0; i -= _(i))
        for(int j = v; j > 0; j -= _(j))
            res = min(res, bit[t][i][j]);
    return res;
}

int solve() {
    FOR(t,1,k) FOR(u,1,m) FOR(v,1,n) bit[t][u][v] = oo;

    int res = 0;
    FOR(i,1,m) FOR(j,1,n) {
        int c = a[i][j];
        FOR(d,1,k) if (has[c][d]) {
            int other = get(d, i, j);
            res = max(res, i + j - other);
        }

        update(c, i, j, i+j);
    }
    return res;
}

int main() {
    while (scanf("%d%d%d%d", &m, &n, &k, &s) == 4) {
        FOR(i,1,m) FOR(j,1,n) scanf("%d", &a[i][j]);
        FOR(i,1,s) scanf("%d", &x[i]);
        memset(has, 0, sizeof has);

        FOR(i,1,s-1) {
            int u = x[i], v = x[i+1];
            has[u][v] = has[v][u] = 1;
        }

        int res = solve();
        FOR(i,1,m) reverse(a[i]+1, a[i]+n+1);
        res = max(res, solve());

        cout << res << endl;
    }
    return 0;
}
