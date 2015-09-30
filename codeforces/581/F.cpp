
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

const int MN = 5011;

int f[2][MN][MN], n, g[MN], sz[MN];
vector< int > ke[MN];

void dfs(int u, int fu) {
    if (SZ(ke[u]) == 1) {
        sz[u] = 1;
        f[0][u][0] = 0; f[0][u][1] = MN;
        f[1][u][1] = 0; f[1][u][0] = MN;
        return ;
    }
    for(int v : ke[u]) {
        if (v == fu) continue;

        dfs(v, u);
        sz[u] += sz[v];
    }

//    DEBUG(u);
    REP(color_u,2) {
        FOR(i,0,sz[u]) g[i] = MN;
        bool first = true;
        int cur = 0;
        for(int v : ke[u]) if (v != fu) {
            cur += sz[v];
            if (first) {
                REP(i,cur+1)
                    g[i] = min(f[color_u][v][i], f[1-color_u][v][i] + 1);
                first = false;
            }
            else {
                FORD(i,cur,0) {
                    g[i] = g[i] + min(f[color_u][v][0], f[1-color_u][v][0] + 1);
                    FOR(j,0,min(sz[v],i))
                        g[i] = min(g[i], g[i-j] + min(f[color_u][v][j], f[1-color_u][v][j] + 1));
                }
            }
//            DEBUG(v);
//            PR0(g, sz[u]+1);
        }
        FOR(i,0,sz[u]) f[color_u][u][i] = g[i];

//        PR0(f[color_u][u], sz[u] + 1);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        if (n == 2) {
            cout << 1 << endl;
            continue;
        }

        int root = 1;
        while (ke[root].size() == 1) ++root;

        dfs(root, -1);
        cout << min(f[0][root][sz[root] / 2], f[1][root][sz[root] / 2]) << endl;
    }
}
