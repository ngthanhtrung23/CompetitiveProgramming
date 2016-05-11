
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

int m, n;
int f[111][111][222];
const int INF = 1000111000111000111LL;

struct Edge {
    int u, v, t, c;
};
vector< Edge > ke[111][111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);

    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> m >> n;
        int startx, starty; cin >> startx >> starty;

        FOR(i,1,m) FOR(j,1,n) ke[i][j].clear();

        int e; cin >> e;
        while (e--) {
            int x, y, u, v, c, t;
            cin >> x >> y >> u >> v >> c >> t;

            Edge cur;
            cur.u = u; cur.v = v;
            cur.c = c;
            cur.t = t;

            ke[x][y].push_back(cur);
        }

        FOR(i,1,m) FOR(j,1,n) REP(t,211) f[i][j][t] = INF;
        f[startx][starty][100] = 0;

        set< pair< pair<int,int>, pair<int,int> > > all;
        all.insert(make_pair(make_pair(0, 100), make_pair(startx, starty)));
        while (!all.empty()) {
            auto it = *all.begin(); all.erase(all.begin());
            int l = it.first.first;
            int t = it.first.second;
            int u = it.second.first;
            int v = it.second.second;
            if (l != f[u][v][t]) continue;

            for(auto e : ke[u][v]) {
                int uu = e.u;
                int vv = e.v;
                int tt = t + e.t;
                if (tt < 0 || tt > 200) continue;
                if (f[uu][vv][tt] > l + e.c) {
                    f[uu][vv][tt] = l + e.c;
                    all.insert(make_pair(make_pair(l + e.c, tt), make_pair(uu, vv)));
                }
            }
        }
        int q; cin >> q;
        cout << "Case " << test << ":\n";
        while (q--) {
            int x, y, t;
            cin >> x >> y >> t;
            t += 100;
            if (f[x][y][t] == INF) cout << "No\n";
            else cout << f[x][y][t] << '\n';
        }
    }
}
