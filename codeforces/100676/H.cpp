
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

int V, E;
vector< vector<int> > G;
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

pair< pair<int,int>, int> edges[200111];

const int MN = 200111;
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

vector< pair<int,int> > ke[MN];

long long dist[MN], f1[MN], f2[MN];

void dfs(int u) {
    for(auto p : ke[u]) {
        int v = p.first;
        if (dist[v] < 0) {
            dist[v] = dist[u] + p.second;
            dfs(v);
        }
    }
}

DSU dsu;
pair<int,int> getDiam() {
    memset(dist, -1, sizeof dist);

    int start = dsu.getRoot(0);
    dist[start] = 0;
    dfs(start);
    int root = max_element(dist, dist+V) - dist;
//    DEBUG(root);

    memset(dist, -1, sizeof dist);
    dist[root] = 0;
    dfs(root);

    int leaf = max_element(dist, dist+V) - dist;
//    DEBUG(leaf);

    return make_pair(root, leaf);
}

int main() {
    ios :: sync_with_stdio(false);
    int test; cin >> test;
    while (test--) {
        G.clear();
        cin >> V >> E;
        G.resize(V);
        FOR(i,1,E) {
            int u, v, c; cin >> u >> v >> c;
            --u; --v;
            G[u].push_back(v);
            G[v].push_back(u);
            edges[i] = make_pair(make_pair(u, v), c);
        }
        UndirectedDfs tree;
        set< pair<int,int> > bridges(tree.bridges.begin(), tree.bridges.end());

        dsu.init(V);
        FOR(i,1,E) {
            int u = edges[i].first.first, v = edges[i].first.second;
            if (bridges.count(make_pair(u, v)) || bridges.count(make_pair(v, u))) {
                continue;
            }
            else dsu.merge(u, v);
        }
        REP(i,V) ke[i].clear();
        FOR(i,1,E) {
            int u = edges[i].first.first, v = edges[i].first.second;
            if (bridges.count(make_pair(u, v)) || bridges.count(make_pair(v, u))) {
                u = dsu.getRoot(u);
                v = dsu.getRoot(v);

                ke[u].push_back(make_pair(v, edges[i].second));
                ke[v].push_back(make_pair(u, edges[i].second));

//                cout << u << ' ' << v << ' ' << edges[i].second << endl;
            }
        }

        auto p = getDiam();
        memset(dist, -1, sizeof dist);
        dist[p.first] = 0;
        dfs(p.first);
        REP(i,V) f1[i] = dist[i];

        memset(dist, -1, sizeof dist);
        dist[p.second] = 0;
        dfs(p.second);
        REP(i,V) f2[i] = dist[i];

//        PR0(f1, V);
//        PR0(f2, V);

        long long best = 1000111000111000;
        REP(i,V) if (i == dsu.getRoot(i)) {
            if (max(f1[i], f2[i]) < best) {
                best = max(f1[i], f2[i]);
            }
        }
        REP(i,V) {
            int x = dsu.getRoot(i);
            if (max(f1[x], f2[x]) == best) {
                cout << i+1 << ' ';
                break;
            }
        }
        cout << best << endl;
    }
    return 0;
}

