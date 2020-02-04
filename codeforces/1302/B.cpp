#include<bits/stdc++.h>
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define PR(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; for(size_t i = 1, _n = n; i <= _n; i++) std::cerr << A[i] << ' '; std::cerr << std::endl; }
#define PR0(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; for(size_t i = 0, _n = n; i < _n; i++) std::cerr << A[i] << ' '; std::cerr << std::endl; }

using AdjList = std::vector<int>;

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    size_t nVertex, nEdge;
    std::cin >> nVertex >> nEdge;
    // Read graph
    std::vector<AdjList> g(nVertex);
    std::vector<int> inDeg(nVertex);

    const auto addEdge = [&g, &inDeg](size_t u, size_t v) {
        g[u].push_back(v);
        inDeg[v]++;
    };

    for (size_t i = 0; i < nEdge; i++) {
        size_t u, v; std::cin >> u >> v;
        assert(1 <= u && u <= nVertex);
        assert(1 <= v && v <= nVertex);
        assert(u != v);

        --u; --v;
        addEdge(v, u);
    }

    // dfs
    std::vector<size_t> order;
    std::vector<bool> visited(nVertex, false);
    std::function<void(int)> dfs;
    dfs = [g, &visited, &order, &dfs] (size_t u) {
        visited[u] = true;
        for (size_t v : g[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
        order.push_back(u);
    };

    for (size_t u = 0; u < nVertex; u++) {
        if (inDeg[u] == 0) {
            assert(!visited[u]);
            dfs(u);
        }
    }

    // calculate
    /** O(N^2) memory
    std::bitset<50000> f[50000];
    for (size_t u : order) {
        f[u].set(u);
        for (size_t v : g[u]) {
            f[u] |= f[v];
        }
    }
    int64_t res = 0;
    for (size_t u = 0; u < nVertex; u++) {
        res += f[u].count() * (int64_t) f[u].count();
    }
    std::cout << res << std::endl;
    */
    std::vector<int> sum(nVertex, 0);
    const int C = 200;
    for (size_t block_start = 0; block_start < nVertex; block_start += C) {
        size_t block_end = block_start + C - 1;
        std::vector<std::bitset<C>> f(nVertex);

        for (size_t u : order) {
            if (block_start <= u && u <= block_end) {
                f[u].set(u - block_start);
            }
            for (auto v : g[u]) {
                f[u] |= f[v];
            }
        }

        for (size_t u = 0; u < nVertex; u++) {
            sum[u] += f[u].count();
        }
    }

    int64_t res = 0;
    for (size_t u = 0; u < nVertex; u++) {
        res += sum[u] * (int64_t) sum[u];
    }
    std::cout << res << std::endl;
}
