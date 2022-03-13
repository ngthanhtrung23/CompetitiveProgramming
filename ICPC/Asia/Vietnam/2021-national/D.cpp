#include <bits/stdc++.h>
using namespace std;

#define SZ(x) ((int)(x).size())
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator << (ostream& out, const Con& con) {
    out << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        out << (it == beg ? "" : ", ") << *it;
    }
    return out << '}';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int r) {
    return uniform_int_distribution<int> (0, r-1)(rng);
}

struct DSU {
    std::vector<int> lab;

    DSU(int n) : lab(n+1, -1) {}

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) std::swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }

    bool same_component(int u, int v) {
        return getRoot(u) == getRoot(v);
    }

    int component_size(int u) {
        return -lab[getRoot(u)];
    }
};

struct Graph {
    Graph(int _n) : n(_n), g(n) {}

    void add_edge(int u, int v, bool bi_directional = false) {
        g[u].push_back(v);
        if (bi_directional) g[v].push_back(u);
    }

    // return
    // - shortest distance from start -> target
    // - path
    // If no path -> returns -1
    pair<int, vector<int>> bfs(int start, int target) const {
        assert(0 <= start && start < n);
        assert(0 <= target && target < n);

        auto [dist, trace] = _bfs({start}, target);
        if (dist[target] < 0) {
            return {dist[target], {}};
        }
        vector<int> path;
        for (int u = target; u != start; u = trace[u]) {
            path.push_back(u);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return {dist[target], path};
    }

    // return: dist: vector<int>, dist[u] = shortest distance from start -> u
    vector<int> bfs(int start) const {
        assert(0 <= start && start < n);
        return _bfs({start}, -1).first;
    }

    // multi-source BFS
    // Return: dist[u] = shortest distance from any source -> u
    vector<int> bfs(vector<int> starts) {
        return _bfs(starts, -1).first;
    }

// private:

    // Start BFS from start, and stop when reaching target.
    // Start = -1 -> BFS whole graph
    // Returns {distance, trace}
    pair<vector<int>, vector<int>> _bfs(vector<int> starts, int target) const {
        assert(-1 <= target && target < n);

        queue<int> qu;
        vector<int> dist(g.size(), -1);
        vector<int> trace(g.size(), -1);

        for (int start : starts) {
            assert(0 <= start && start < n);
            dist[start] = 0;
            qu.push(start);
        }

        while (!qu.empty()) {
            auto u = qu.front(); qu.pop();
            if (u == target) {
                break;
            }

            for (const auto& v : g[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    trace[v] = u;
                    qu.push(v);
                }
            }
        }

        return {dist, trace};
    }

    int n;
    vector<vector<int>> g;
};

void print_answer(
        const Graph& g,
        const std::vector<std::pair<int, int>> added_edges,
        const std::vector<std::pair<int, int>> outer_edges) {
    std::cout << "YES\n";
    std::cout << added_edges.size() << '\n';
    for (auto [u, v] : added_edges) {
        std::cout << 1+u << ' ' << 1+v << '\n';
    }

    for (auto [u, v] : outer_edges) {
        auto [len, path] = g.bfs(u, v);
        std::cout << len + 1;
        for (int x : path) std::cout << ' ' << 1+x;
        std::cout << '\n';
    }
}

int main() {
    // read input
    int n, m, k; std::cin >> n >> m >> k;
    int max_cycles = n * (n-1) / 2 - (n-1);
    if (k > max_cycles) {
        std::cout << "NO\n";
        return 0;
    }

    Graph tree(n);
    std::vector<std::pair<int,int>> outer_edges;
    std::vector<std::vector<bool>> has_edge(n, std::vector<bool> (n, false));

    // build DSU
    DSU dsu(n);
    while (m--) {
        int u, v; std::cin >> u >> v;
        --u; --v;
        has_edge[u][v] = has_edge[v][u] = true;

        if (dsu.same_component(u, v)) {
            outer_edges.emplace_back(u, v);
        } else {
            dsu.merge(u, v);
            tree.add_edge(u, v, true);
        }
    }

    if (SZ(outer_edges) >= k) {
        outer_edges.resize(k);
        print_answer(tree, {}, outer_edges);
        return 0;
    }

    // put vertices into components
    std::vector<int> component_ids(n, -1);
    std::vector<std::vector<int>> components;
    for (int i = 0; i < n; i++) {
        int u = dsu.getRoot(i);
        if (component_ids[u] < 0) {
            component_ids[u] = components.size();
            components.emplace_back();
        }

        components[component_ids[u]].push_back(i);
    }

    // larger component first
    std::sort(components.begin(), components.end(),
            [] (const std::vector<int>& a, const std::vector<int>& b) {
                return a.size() > b.size();
            });

    std::vector<std::pair<int, int>> added_edges;

    // add edges in same component
    for (auto comp : components) {
        for (int i = 0; i < SZ(comp); i++) {
            for (int j = i + 1; j < SZ(comp); j++) {
                int u = comp[i], v = comp[j];
                if (!has_edge[u][v]) {
                    added_edges.emplace_back(u, v);
                    outer_edges.emplace_back(u, v);

                    if (SZ(outer_edges) >= k) {
                        print_answer(tree, added_edges, outer_edges);
                        return 0;
                    }
                }
            }
        }
    }

    // connect different components
    for (int i = 1; i < SZ(components); i++) {
        bool first = true;
        for (int u : components[0]) {
            for (int v : components[i]) {
                added_edges.emplace_back(u, v);
                if (first) {
                    first = false;
                    tree.add_edge(u, v, true);
                } else {
                    outer_edges.emplace_back(u, v);
                }

                if (SZ(outer_edges) >= k) {
                    print_answer(tree, added_edges, outer_edges);
                    return 0;
                }
            }
        }

        components[0].insert(components[0].end(), components[i].begin(), components[i].end());
    }
    return 0;
}
