#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

vector< int > G[10111];
int V;

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

int lab[10111];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}
void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
    if (u == v) return ;
    lab[u] = lab[u] + lab[v];
    lab[v] = u;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n, m, q;
    while (cin >> n >> m >> q && n) {
        V = n;
        REP(i,n) G[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            --u; --v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        UndirectedDfs tree;
        memset(lab, -1, sizeof lab);
        for(auto p : tree.bridges) {
            int u = p.first, v = p.second;
            ++u; ++v;
            merge(u, v);
        }

        while (q--) {
            int u, v; cin >> u >> v;
            if (getRoot(u) == getRoot(v)) cout << 'Y';
            else cout << 'N';
            cout << "\n";
        }
        cout << "-\n";
    }
    return 0;
}
