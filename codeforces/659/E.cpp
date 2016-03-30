
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

const int MN = 100111;
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
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
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

set< pair<int,int> > bridges;
int visited[MN];

void dfs(int u) {
    visited[u] = true;
    for(int v : G[u]) {
        if (!visited[v]) dfs(v);
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int m;
    while (scanf("%lld%lld", &V, &m) == 2) {
        REP(i,V) G[i].clear();
        REP(i,m) {
            int u, v; scanf("%lld%lld", &u, &v);
            --u; --v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        UndirectedDfs tree;

        bridges.clear();
        for(auto b : tree.bridges) {
            bridges.insert(b);
            bridges.insert(make_pair(b.second, b.first));
        }

        int n = V;
        DSU dsu;
        dsu.init(n);

        REP(u,n) for(int v : G[u]) {
            if (bridges.find(make_pair(u, v)) != bridges.end()) continue;
            dsu.merge(u, v);
        }

        int res = 0;
        memset(visited, 0, sizeof visited);

        // first, we DFS from all good vertices
        REP(u,n) {
            int r = dsu.getRoot(u);
            int cnt = -dsu.lab[r];
            
            if (cnt > 1 && !visited[u]) {
                dfs(u);
            }
        }

        REP(u,n) if (!visited[u]) {
            ++res;
            dfs(u);
        }
        cout << res << endl;
    }
}
