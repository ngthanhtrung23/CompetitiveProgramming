#include "bits/stdc++.h"

struct Edge {
    int to;
    int x, y;
};
std::vector<std::vector<Edge>> g;
std::vector<int> colors;

void dfs(int u, int c) {
    if (colors[u] >= 0) {
        if (colors[u] != c) throw 1;
        return;
    }
    colors[u] = c;

    for (auto e : g[u]) {
        if (e.x != c && e.y != c) throw 1;
        if (e.x == e.y) continue;  // handle outside

        if (e.x == c) {
            dfs(e.to, e.y);
        } else {
            assert(e.y == c);
            dfs(e.to, e.x);
        }
    }
}

int32_t main() {
    int n, m; std::cin >> n >> m;
    g.resize(n);
    colors = std::vector<int> (n, -1);
    while (m--) {
        int u, v, x, y; std::cin >> u >> v >> x >> y;
        --u; --v;

        g[u].push_back({v, x, y});
        g[v].push_back({u, x, y});
    }

    try {
        // edge (u, v, x, x) -> colors[u] = colors[v] = x
        for (int u = 0; u < n; u++) {
            for (const auto& e : g[u]) {
                if (e.x == e.y) {
                    dfs(u, e.x);
                    dfs(e.to, e.x);
                }
            }
        }

        // edge (u, _, x, y) and edge(u, _, x, z) -> colors[u] = x
        for (int u = 0; u < n; u++) {
            if (g[u].empty()) continue;

            int x = g[u][0].x;
            int y = g[u][0].y;

            for (const auto& e : g[u]) {
                if (x != e.x && x != e.y) x = -1;
                if (y != e.x && y != e.y) y = -1;
            }

            if (x < 0) dfs(u, y);
            if (y < 0) dfs(u, x);
        }
    } catch (...) {
        std::cout << -1 << std::endl;
        return 0;
    }
    
    for (int u = 0; u < n; u++) {
        if (colors[u] < 0 && !g[u].empty()) {
            dfs(u, g[u][0].x);
        }
    }

    for (int i = 0; i < n; i++) {
        if (colors[i] < 0) std::cout << 10;
        else std::cout << colors[i];
        std::cout << ' ';
    }
    std::cout << std::endl;
    return 0;
}
