#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 20111;
int lab[MN];
struct DSU {
    void init(int n) {
        for (int i = 0; i <= n; i++) lab[i] = -1;
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

struct Edge {
    int u, v, c;
};
bool operator < (const Edge& e1, const Edge& e2) {
    return e1.c < e2.c;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<Edge> edges(m);
    for (auto& e : edges) {
        cin >> e.u >> e.v >> e.c;
    }
    sort(edges.begin(), edges.end());

    DSU dsu;
    dsu.init(n);

    int res = 0;
    for (auto e : edges) {
        if (dsu.getRoot(e.u) == dsu.getRoot(e.v)) {
            continue;
        }
        dsu.merge(e.u, e.v);
        res += e.c;
    }
    cout << res << endl;

    for (int i = 1; i <= n; i++) {
        assert(dsu.getRoot(i) == dsu.getRoot(1));
    }
    return 0;
}
