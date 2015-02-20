
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
const long long MOD = 1000000007;

long long p2[MN];
int n, m, V;
vector< vector<int> > G;

struct Undirecteddfs1 {
    vector<int> low, num, parent;
    vector<bool> articulation;
    int counter, root, children;

    vector< pair<int,int> > bridges;
    vector<int> cuts;

    Undirecteddfs1() : low(V, 0), num(V, -1), parent(V, 0), articulation(V, false),
            counter(0), children(0) {
        for(int i = 0; i < V; ++i) if (num[i] == -1) {
            root = i; children = 0;
            dfs1(i);
            articulation[root] = (children > 1);
        }
        for(int i = 0; i < V; ++i)
            if (articulation[i]) cuts.push_back(i);
    }
private:
    void dfs1(int u) {
        low[u] = num[u] = counter++;
        for(int j = 0; j < G[u].size(); ++j) {
            int v = G[u][j];
            if (num[v] == -1) {
                parent[v] = u;
                if (u == root) children++;
                dfs1(v);
                if (low[v] >= num[u])
                    articulation[u] = true;
                if (low[v] > num[u]) bridges.push_back(make_pair(u, v));
                low[u] = min(low[u], low[v]);
            } else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
};


int eu[MN], ev[MN];
set< pair<int,int> > bridges;
int componentId[MN], componentSize[MN], nComponents;
int isLoop[MN], h[MN], f[MN], father[22][MN];

set< int > ke[MN];

void dfs1(int u) {
    componentId[u] = nComponents;
    componentSize[nComponents]++;
    for(int v : G[u]) {
        if (componentId[v] >= 0) continue;
        if (bridges.count(make_pair(u, v)) || bridges.count(make_pair(v, u))) continue;

        dfs1(v);
    }
}

void dfs2(int u, int fu) {
    f[u] = isLoop[u];
    if (fu >= 0) f[u] += f[fu];

    for(int v : ke[u]) {
        if (v == fu) continue;

        h[v] = h[u] + 1;
        father[0][v] = u;

        dfs2(v, u);
    }
}

void init() {
    FOR(t,1,17) {
        FOR(u,1,nComponents) {
            father[t][u] = father[t-1][ father[t-1][u] ];
        }
    }
}

int lca(int u, int v) {
    if (h[u] != h[v]) {
        if (h[u] > h[v]) swap(u, v);
        FORD(t,17,0) {
            if (h[ father[t][v] ] >= h[u]) {
                v = father[t][v];
            }
        }
    }
    if (u == v) return u;

    FORD(t,17,0)
        if (father[t][u] != father[t][v]) {
            u = father[t][u];
            v = father[t][v];
        }
    return father[0][u];
}

int main() {
    p2[0] = 1; FOR(i,1,MN-1) p2[i] = (2 * p2[i-1]) % MOD;
    while (scanf("%d%d", &n, &m) == 2) {
        V = n;
        G.resize(n);
        REP(i,n) G[i].clear();
        FOR(i,1,m) {
            scanf("%d%d", &eu[i], &ev[i]);
            --eu[i]; --ev[i];

            G[eu[i]].push_back(ev[i]);
            G[ev[i]].push_back(eu[i]);
        }

        Undirecteddfs1 tree;
//        DEBUG(tree.bridges.size());
        for(auto p : tree.bridges) {
//            cout << p.first << ' ' << p.second << endl;

            bridges.insert(p);
        }

        memset(componentId, -1, sizeof componentId);
        memset(componentSize, 0, sizeof componentSize);

        REP(i,n) if (componentId[i] < 0) {
            ++nComponents;
            dfs1(i);
        }

//        DEBUG(nComponents);
//        PR0(componentId, n);
//        PR(componentSize, nComponents);

        FOR(i,1,n) ke[i].clear();
        FOR(i,1,nComponents) {
            isLoop[i] = (componentSize[i] > 1) ? 1 : 0;
        }

        FOR(i,1,m) {
            int u = componentId[eu[i]], v = componentId[ev[i]];
            if (u != v && !ke[u].count(v)) {
                ke[u].insert(v);
                ke[v].insert(u);
//                cout << u << ' ' << v << endl;
            }
        }

        h[1] = 1;
        dfs2(1, -1);
//        PR(isLoop, nComponents);
//        PR(f, nComponents);

        init();

        int q; scanf("%d", &q);
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            --u; --v;

            u = componentId[u];
            v = componentId[v];
            
//            cout << u << ' ' << v << endl;

            int res = 0;
            if (u == v) res = p2[ isLoop[u] ];
            else {
                int l = lca(u, v);
//                DEBUG(l);
                if (l == v) swap(u, v);
                if (l == u) res = p2[ f[v] - f[father[0][u]] ];
                else {
                    res = p2[ f[u] + f[v] - f[l] - f[ father[0][l] ]];
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
