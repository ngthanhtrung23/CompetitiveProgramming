#include<bits/stdc++.h>
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define PR0(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; for(size_t i = 0, _n = n; i < _n; i++) std::cerr << A[i] << ' '; std::cerr << std::endl; }

struct Edge {
    size_t to;
    int64_t cost;

    Edge(size_t to, int64_t cost) : to(to), cost(cost) {}
};

using AdjList = std::vector<Edge>;

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    size_t nVertex, nEdge; std::cin >> nVertex >> nEdge;

    std::vector<AdjList> g(nVertex);
    auto addEdge = [&g] (size_t from, size_t to, int64_t cost) {
        g[from].emplace_back(to, cost);
    };
    for (size_t _ = 0; _ < nEdge; _++) {
        size_t u, v;
        int64_t cost;
        std::cin >> u >> v >> cost;
        --u; --v;
        addEdge(u, v, cost);
        addEdge(v, u, cost);
    }

    std::set<std::pair<int64_t, int>> all;
    const long long INF = 1000111000111000LL;
    std::vector<int64_t> f(nVertex, INF);
    f[0] = 0;
    all.insert({0, 0});
    std::vector<bool> finalized(nVertex, false);

    while (!all.empty()) {
        auto it = prev(all.end());
        auto u = it->second;
        all.erase(it);

        if (finalized[u]) continue;
        finalized[u] = true;

        for (auto e : g[u]) {
            if (f[e.to] > f[u] + e.cost) {
                f[e.to] = f[u] + e.cost;
                all.insert({f[e.to], e.to});
            }
        }
    }
    std::cout << (f[nVertex-1] == INF ? -1 : f[nVertex-1]) << std::endl;
}
