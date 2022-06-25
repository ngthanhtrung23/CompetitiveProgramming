#include "bits/stdc++.h"

struct UndirectedDfs {
    std::vector<std::vector<int>> g;
    int n;
    std::vector<int> low, num, parent;
    std::vector<bool> is_articulation;
    int counter, root, children;

    std::vector< std::pair<int,int> > bridges;
    std::vector<int> articulation_points;
    std::map<std::pair<int,int>, int> cnt_edges;

    UndirectedDfs(const std::vector<std::vector<int>>& _g) : g(_g), n(g.size()),
            low(n, 0), num(n, -1), parent(n, 0), is_articulation(n, false),
            counter(0), children(0) {
        for (int u = 0; u < n; u++) {
            for (int v : g[u]) {
                cnt_edges[{u, v}] += 1;
            }
        }
        for(int i = 0; i < n; ++i) if (num[i] == -1) {
            root = i; children = 0;
            dfs(i);
            is_articulation[root] = (children > 1);
        }
        for(int i = 0; i < n; ++i)
            if (is_articulation[i]) articulation_points.push_back(i);
    }
private:
    void dfs(int u) {
        low[u] = num[u] = counter++;
        for (int v : g[u]) {
            if (num[v] == -1) {
                parent[v] = u;
                if (u == root) children++;
                dfs(v);
                if (low[v] >= num[u])
                    is_articulation[u] = true;
                if (low[v] > num[u]) {
                    if (cnt_edges[{u, v}] == 1) {
                        bridges.push_back(std::make_pair(u, v));
                    }
                }
                low[u] = std::min(low[u], low[v]);
            } else if (v != parent[u])
                low[u] = std::min(low[u], num[v]);
        }
    }
};

std::vector<int> sz, parent, componentId;
std::vector<std::vector<int>> g;

void dfs(int u, int c) {
    sz[u] = 1;
    componentId[u] = c;
    for (int v : g[u]) {
        if (sz[v] == 0) {
            parent[v] = u;
            dfs(v, c);

            sz[u] += sz[v];
        }
    }
}

std::bitset<50001> f[2];

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n, m; std::cin >> n >> m;
    g.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v; std::cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    sz.resize(n);
    parent.resize(n);
    componentId.resize(n);

    int nComponents = 0;
    std::vector<int> componentSizes;
    for (int i = 0; i < n; i++) {
        if (sz[i] == 0) {
            parent[i] = -1;
            dfs(i, nComponents);
            ++nComponents;

            componentSizes.push_back(sz[i]);
        }
    }

    UndirectedDfs tree(g);
    std::vector<std::vector<int>> szHalf(nComponents);
    for (auto [u, v] : tree.bridges) {
        if (v == parent[u]) std::swap(u, v);
        assert(componentId[u] == componentId[v]);
        assert(sz[v] < sz[u]);
        szHalf[componentId[v]].push_back(sz[v]);
    }

    // f[0] = have not used any bridge
    // f[1] = used exactly 1 bridge
    f[0][0] = 1;
    for (int i = 0; i < nComponents; i++) {
        f[1] |= f[1] << componentSizes[i];

        for (int s : szHalf[i]) {
            f[1] |= f[0] << s;
            f[1] |= f[0] << (componentSizes[i] - s);
        }

        f[0] |= f[0] << componentSizes[i];
    }

    const long long INF = 1e18 + 11;
    long long res = INF;

    auto C2 = [] (long long x) {
        return x * (x - 1LL) / 2;
    };

    for (int s = 1; s <= n / 2; s++) {
        if (f[0][s] || f[1][s]) {
            res = std::min(res, 1 + C2(s) + C2(n - s) - m);
        }
    }

    if (res == INF) res = -1;
    std::cout << res << std::endl;

    return 0;
}
