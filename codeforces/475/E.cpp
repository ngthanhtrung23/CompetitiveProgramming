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
int V;
vector<int> G[MN];

struct UndirectedDfs {
    vector<int> low, num, parent;
    vector<bool> articulation;
    int counter, root, children;

    vector< pair<int,int> > bridges;
    vector<int> cuts;

    UndirectedDfs() : low(V, 0), num(V, -1), parent(V, 0), articulation(V, false),
            counter(0), children(0) {
        for(int i = 0; i < V; ++i) if (num[i] == -1) {
            root = i; children = 0;
            dfs(i);
            articulation[root] = (children > 1);
        }
        for(int i = 0; i < V; ++i)
            if (articulation[i]) cuts.push_back(i);
    }
private:
    void dfs(int u) {
        low[u] = num[u] = counter++;
        for(int j = 0; j < G[u].size(); ++j) {
            int v = G[u][j];
            if (num[v] == -1) {
                parent[v] = u;
                if (u == root) children++;
                dfs(v);
                if (low[v] >= num[u])
                    articulation[u] = true;
                if (low[v] > num[u]) bridges.push_back(make_pair(u, v));
                low[u] = min(low[u], low[v]);
            } else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
};

struct DSU {
    int lab[MN];
    void init() {
        memset(lab, -1, sizeof lab);
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

int weight[MN], sz[MN];
vector<int> ke[MN];

int dfs(int u, int fu) {
    int res = weight[u] * weight[u];
    sz[u] = weight[u];

    vector<int> x;
    for(int v : ke[u]) {
        if (v == fu) continue;
        res += dfs(v, u);
        sz[u] += sz[v];
        res += sz[v] * weight[u];

        if (fu == -1) x.push_back(sz[v]);
    }

    if (fu == -1) {
        int sumx = 0;
        for(int t : x) sumx += t;
        vector< vector<bool> > f;
        f.resize(x.size() + 1);
        REP(i,f.size()) {
            f[i].resize(sumx + 1);
            REP(j,f[i].size()) f[i][j] = false;
        }

        f[0][0] = true;
        REP(i,x.size()) FOR(cur,0,sumx) if (f[i][cur]) {
            f[i+1][cur] = true;
            f[i+1][cur + x[i]] = true;
        }

        int best = 0;

        FOR(in,0,sumx) if (f[x.size()][in]) {
            int out = sumx - in;
            best = max(best, in * out);
        }
        res += best;
    }
    
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int m;
    while (cin >> V >> m) {
        REP(i,V) {
            G[i].clear();
            ke[i].clear();
        }
        while (m--) {
            int u, v; cin >> u >> v; --u; --v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        UndirectedDfs tree;
        set< pair<int,int> > bridges;
        for(auto e : tree.bridges) {
            bridges.insert(e);
            bridges.insert(make_pair(e.second, e.first));
        }

        DSU dsu;
        dsu.init();
        REP(u,V) for(int v : G[u]) {
            if (bridges.count(make_pair(u, v))) continue;
            dsu.merge(u, v);
        }

//        REP(i,V) cout << dsu.getRoot(i) << ' '; cout << endl;

        REP(i,V) if (dsu.lab[i] < 0) weight[i] = -dsu.lab[i]; else weight[i] = 0;
//        PR0(weight, V);

        REP(u,V) for(int v : G[u]) {
            int i = dsu.getRoot(u);
            int j = dsu.getRoot(v);
            if (i != j) {
                ke[i].push_back(j);
            }
        }

        int res = 0;
        REP(u,V) if (dsu.lab[u] < 0) {
            res = max(res, dfs(u, -1));
        }
        cout << res << endl;

//        DEBUG("OK");
    }
    return 0;
}
