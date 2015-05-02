
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

int V;
vector< vector<int> > G;
struct UndirectedDfs {
    vector<int> low, num, parent;
    int counter, root, components;

    vector< pair<int,int> > bridges;

    UndirectedDfs() : low(V, 0), num(V, -1), parent(V, 0),
            counter(0) {
        components = 0;
        for(int i = 0; i < V; ++i) if (num[i] == -1) {
            root = i;
            ++components;
            if (components > 1) return ;
            dfs(i);
        }
    }
private:
    void dfs(int u) {
        low[u] = num[u] = counter++;
        for(int j = 0; j < G[u].size(); ++j) {
            int v = G[u][j];
            if (num[v] == -1) {
                parent[v] = u;
                dfs(v);
                if (low[v] > num[u]) bridges.push_back(make_pair(u, v));
                low[u] = min(low[u], low[v]);
            } else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
};


pair< pair<int,int>, int > edges[22];
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int main() {
    ios :: sync_with_stdio(false);
    int E, test = 0;
    while (cin >> V >> E) {
        if (V == 0 && E == 0) break;
        G.resize(V);
        REP(i,V) G[i].resize(V);

        REP(i,E) {
            int u, v, c; cin >> u >> v >> c;
            --u; --v;
            edges[i] = make_pair(make_pair(u, v), c);
        }

        int res = 1000111000;
        REP(mask,TWO(E)) if (__builtin_popcount(mask) >= V) {
            REP(i,V) G[i].clear();

            int cur = 0;
            REP(i,E) {
                int u = edges[i].first.first, v = edges[i].first.second;

                if (CONTAIN(mask,i)) {
                    cur += edges[i].second;
                    G[u].push_back(v);
                    G[v].push_back(u);
                }
            }
            UndirectedDfs tree;
            if (tree.components == 1 && tree.bridges.empty()) res = min(res, cur);

        }
        if (res == 1000111000) cout << "There is no reliable net possible for test case "
            << ++test << ".\n";
        else cout << "The minimal cost for test case " << ++test << " is " << res << ".\n";
    }
    return 0;
}
