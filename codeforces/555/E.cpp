
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

const int MN = 500111;

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


int n, m, q, comId[MN], nCom;
vector< int > ke[MN], com_ke[MN];
set< pair<int,int> > bridges, tree_edges;
map< pair<int,int>, int > cnt;
int father[22][MN], isUp[22][MN], isDown[22][MN], h[MN];

void init() {
    REP(i,n+2) {
        ke[i].clear();
        com_ke[i].clear();
    }
    bridges.clear();
    tree_edges.clear();
    cnt.clear();
    memset(comId, -1, sizeof comId);

    memset(h, -1, sizeof h);
    memset(father, 0, sizeof father);
    memset(isUp, 0, sizeof isUp);
    memset(isDown, 0, sizeof isDown);
}

struct UndirectedDfs {
    vector<int> low, num, parent;
    int counter, root, children;

    vector< pair<int,int> > bridges;
    vector<int> cuts;

    UndirectedDfs() : low(n, 0), num(n, -1), parent(n, 0),
            counter(0), children(0) {
        for(int i = 0; i < n; ++i) if (num[i] == -1) {
            root = i; children = 0;
            dfs(i);
        }
    }
private:
    void dfs(int u) {
        low[u] = num[u] = counter++;
        for(int j = 0; j < ke[u].size(); ++j) {
            int v = ke[u][j];
            if (num[v] == -1) {
                parent[v] = u;
                if (u == root) children++;
                dfs(v);
                if (low[v] > num[u]) bridges.push_back(make_pair(u, v));
                low[u] = min(low[u], low[v]);
            } else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
};

void dfs(int u, int com) {
    comId[u] = com;
    for(int v : ke[u]) {
        if (bridges.count(make_pair(u, v)) || bridges.count(make_pair(v, u))) continue;
        if (comId[v] < 0) {
            dfs(v, com);
        }
    }
}

void dfs2(int u, int fu) {
    father[0][u] = fu;
    for(int v : com_ke[u]) {
        if (v == fu) continue;

        h[v] = h[u] + 1;
        dfs2(v, u);
    }
}

void initLCA() {
    FOR(t,1,20) {
        FOR(u,1,nCom) {
            father[t][u] = father[t-1][ father[t-1][u] ];
        }
    }
}

void go(int u, int v) {
    if (u == v) return ;
    if (h[u] < h[v]) {
        FORD(t,20,0) {
            int x = father[t][v];
            if (h[x] >= h[u]) {
                isDown[t][v] = true;
                v = x;
            }
        }
    }
    if (h[u] > h[v]) {
        FORD(t,20,0) {
            int x = father[t][u];
            if (h[x] >= h[v]) {
                isUp[t][u] = true;
                u = x;
            }
        }
    }
    if (u == v) return ;
    FORD(t,20,0)
        if (father[t][u] != father[t][v]) {
            isUp[t][u] = isDown[t][v] = true;
            u = father[t][u];
            v = father[t][v];
        }
    isUp[0][u] = isDown[0][v] = true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> q) {
        DSU dsu;
        dsu.init(n);

        init();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            --u; --v;

            dsu.merge(u, v);
            ke[u].push_back(v);
            ke[v].push_back(u);
//            cout << u << ' ' << v << endl;

            cnt[make_pair(u, v)]++;
            cnt[make_pair(v, u)]++;
        }
        UndirectedDfs tree;
        for(auto p : tree.bridges) {
            if (cnt[p] == 1) {
                bridges.insert(p);
                bridges.insert(make_pair(p.second, p.first));
            }
        }

//        cout << "Bridges: "; for(auto p : bridges) cout << p.first << ' ' << p.second << "   "; cout << endl;

        nCom = 0;
        REP(i,n) if (comId[i] < 0) {
            ++nCom;

            dfs(i, nCom);
        }
//        PR0(comId, n);

//        cout << "Tree: " << endl;
        REP(i,n) {
            for(int j : ke[i]) {
                int u = comId[i], v = comId[j];
                if (u == v) continue;

                if (tree_edges.count(make_pair(u, v))) continue;
                if (tree_edges.count(make_pair(v, u))) continue;

                tree_edges.insert(make_pair(u, v));
                com_ke[u].push_back(v);
                com_ke[v].push_back(u);

//                cout << i << ' ' << j << " --> ";
//                cout << u << ' ' << v << endl;
            }
        }

        FOR(i,1,nCom) if (h[i] < 0) {
            h[i] = 1;
            dfs2(i, 0);
        }
        initLCA();

        bool ok = true;
        while (q--) {
            int u, v; cin >> u >> v;
            --u; --v;
            if (dsu.getRoot(u) != dsu.getRoot(v)) ok = false;
            u = comId[u];
            v = comId[v];
            go(u, v);
        }
        FORD(t,20,1) {
            FOR(u,1,nCom) {
                if (isUp[t][u]) {
                    int x = father[t-1][u];
                    isUp[t-1][u] = isUp[t-1][x] = true;
                }
                if (isDown[t][u]) {
                    int x = father[t-1][u];
                    isDown[t-1][u] = isDown[t-1][x] = true;
                }
            }
        }
        FOR(i,1,nCom) if (isUp[0][i] && isDown[0][i]) ok = false;

        cout << (ok ? "Yes" : "No") << endl;
    }
}

