
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

const int MN = 211;

int n;
vector<int> ke[MN];
int color[MN];
int c[MN][MN];
int eu[MN], ev[MN];

void dfs1(int u, int fu, int blocked, int c) {
    color[u] = c;
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;
        if (v == blocked) continue;

        dfs1(v, u, blocked, c);
    }
}

void dfs2(int u, int fu, int root) {
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;
        if (color[v] != color[u]) continue;

        c[root][v] = c[root][u] + 1;
        dfs2(v, u, root);
    }
}

int main() {
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);

            eu[i] = u;
            ev[i] = v;
        }
        int res = 0;
        FOR(edge_id,2,n) {
            int u = eu[edge_id], v = ev[edge_id];
            dfs1(u, -1, v, 1);
            dfs1(v, -1, u, 2);

            FOR(i,1,n) FOR(j,1,n) c[i][j] = (i == j) ? 0 : 1e9;

            FOR(i,1,n) {
                dfs2(i, -1, i);
            }

            int max1 = 0, max2 = 0;

            FOR(x,1,n) FOR(y,1,n)
                if (c[x][y] < MN) {
                    if (color[x] == 1) max1 = max(max1, c[x][y]);
                    else max2 = max(max2, c[x][y]);
                }

            res = max(res, max1 * max2);
        }
        cout << res << endl;
    }
}
