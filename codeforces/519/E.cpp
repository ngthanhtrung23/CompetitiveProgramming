
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

const int MN = 100111;

int n, h[MN], father[22][MN], sz[MN];
vector<int> ke[MN];

void dfs(int u, int fu) {
    sz[u] = 1;
    for(auto v : ke[u]) {
        if (v == fu) continue;

        h[v] = h[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
        father[0][v] = u;
    }
}

void initLCA() {
    FOR(t,1,20)
        FOR(u,1,n)
            father[t][u] = father[t-1][ father[t-1][u] ];
}

int lca(int u, int v) {
    if (u == v) return u;
    if (h[u] != h[v]) {
        if (h[u] > h[v]) swap(u, v);
        // h[v] > h[u]

        FORD(i,20,0)
            if (h[father[i][v]] >= h[u]) {
                v = father[i][v];
            }
    }
    if (u == v) return u;
    FORD(i,20,0)
        if (father[i][u] != father[i][v]) {
            u = father[i][u];
            v = father[i][v];
        }
    return father[0][u];
}

int up(int u, int x) {
    if (x == 0) return u;
    FORD(i,20,0)
        if (x >= (1<<i)) {
            u = father[i][u];
            x -= 1<<i;
        }
    return u;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        memset(father, 0, sizeof father);
        h[1] = 1;
        dfs(1, -1);

        initLCA();

        int q; scanf("%d", &q);
        while (q--) {
            int x, y; scanf("%d%d", &x, &y);
            if (x == y) printf("%d\n", n);
            else {
                int l = lca(x, y);
                int len = h[x] + h[y] - 2 * h[l];
                if (len % 2 == 1) puts("0");
                else {
                    int lx = h[x] - h[l];
                    int ly = h[y] - h[l];

                    if (lx == ly) {
                        int xx = up(x, lx-1);
                        int yy = up(y, ly-1);

                        printf("%d\n", n - sz[xx] - sz[yy]);
                    }
                    else {
                        if (lx < ly) swap(x, y);
                        // lx > ly

                        int xx = up(x, len / 2);
                        printf("%d\n", sz[xx] - sz[up(x, len / 2 - 1)]);
                    }
                }
            }
        }
    }
    return 0;
}
