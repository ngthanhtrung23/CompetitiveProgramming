
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
using namespace std;

int V;
vector<int> G[10111];
map< pair<int,int>, int > cnt;
map< pair<int,int>, int > id;

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


int main() {
    ios :: sync_with_stdio(false);
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
    int E;
    while (cin >> V >> E) {
        cnt.clear();
        id.clear();
        REP(i,V) G[i].clear();
        FOR(i,1,E) {
            int u, v; cin >> u >> v;
            --u; --v;
            G[u].push_back(v);
            G[v].push_back(u);

            id[make_pair(u, v)] = id[make_pair(v, u)] = i;
            cnt[make_pair(u, v)] += 1;
            cnt[make_pair(v, u)] += 1;
        }

        UndirectedDfs tree;
        vector<int> res;
        for(auto p : tree.bridges) {
            if (cnt[p] > 1) continue;

            res.push_back(id[p]);
        }
        printf("%d\n", res.size());
        for(int x : res) printf("%d ", x); puts("");
    }
}
