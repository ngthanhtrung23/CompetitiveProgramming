
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

const int MN = 200111;
int n, m;
vector<int> ke[MN];
int sz[MN], max_child[MN], sum_child[MN];

struct UndirectedDfs {
    vector<int> low, num, parent;
    vector<bool> articulation;
    int counter, root, children;

    vector< pair<int,int> > bridges;
    vector<int> cuts;

    UndirectedDfs() : low(n, 0), num(n, -1), parent(n, 0), articulation(n, false),
            counter(0), children(0) {
        for(int i = 0; i < n; ++i) if (num[i] == -1) {
            root = i; children = 0;
            dfs(i);
            articulation[root] = (children > 1);
        }
        for(int i = 0; i < n; ++i)
            if (articulation[i]) cuts.push_back(i);
    }
private:
    void dfs(int u) {
        sz[u] = 1;
        max_child[u] = 0;
        sum_child[u] = 0;
        low[u] = num[u] = counter++;
        for(int j = 0; j < ke[u].size(); ++j) {
            int v = ke[u][j];
            if (num[v] == -1) {
                parent[v] = u;
                if (u == root) children++;
                dfs(v);
                sz[u] += sz[v];

                if (low[v] >= num[u]) {
                    articulation[u] = true;
                    max_child[u] = max(max_child[u], sz[v]);
                    sum_child[u] += sz[v];
                }
                if (low[v] > num[u]) bridges.push_back(make_pair(u, v));
                low[u] = min(low[u], low[v]);
            } else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
};


int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        REP(i,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            --u; --v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        UndirectedDfs tree;

//        PR0(sz, n);
//        PR0(max_child, n);
//        PR0(sum_child, n);

        int res = n, save = 0;
        REP(i,n) if (tree.articulation[i]) {
            int cur = max_child[i];
            cur = max(cur, n - 1 - sum_child[i]);

            if (cur < res) {
                res = cur;
                save = i;
            }
        }
//        DEBUG(res);
        cout << save + 1 << endl;
    }
}

