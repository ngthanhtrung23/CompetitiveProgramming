
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int V, res[20111], sz[20111];
vector<int> G[20111];
vector<int> child[20111];

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
            parent[i] = -1;
            dfs(i);
            articulation[root] = (children > 1);
        }
        for(int i = 0; i < V; ++i)
            if (articulation[i]) cuts.push_back(i);
    }
private:
    void dfs(int u) {
        low[u] = num[u] = counter++;
        sz[u] = 1;
        for(int j = 0; j < G[u].size(); ++j) {
            int v = G[u][j];
            if (num[v] == -1) {
                parent[v] = u;
                if (u == root) children++;
                dfs(v);
                sz[u] += sz[v];
                if (low[v] >= num[u]) {
                    articulation[u] = true;
                    child[u].push_back(sz[v]);
                }
                if (low[v] > num[u]) bridges.push_back(make_pair(u, v));
                low[u] = min(low[u], low[v]);
            } else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
};

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    int E;
    while (scanf("%d%d", &V, &E) == 2) {
        REP(i,V) {
            G[i].clear();
            child[i].clear();
        }
        REP(i,V) res[i] = 0;
        REP(i,E) {
            int u, v; scanf("%d%d", &u, &v);
            --u; --v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        UndirectedDfs tree;
        for(auto u : tree.cuts) {
            int sum = 0;
            for(int x : child[u]) {
                res[u] += x * sum;
                sum += x;
            }
            res[u] += (V - 1 - sum) * sum;
        }
        REP(i,V) res[i] += V - 1;
        REP(i,V) printf("%d\n", res[i]);
    }
}
