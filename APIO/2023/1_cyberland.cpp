// Solution write up: https://www.facebook.com/code.cung.rr/posts/pfbid0fHQPst4qABCYqGoFJ8L9mXUmN4T1zB78mDSbynM6xt1RLx1TruhsgWfkaqmwfSkgl
#include "cyberland.h"
#include <bits/stdc++.h>
#define SZ(s) ((int) ((s).size()))
using namespace std;
 
const int ZERO = 0;
const int NORMAL = 1;
const int DIV2 = 2;
 
void upMin(double& res, double val) {
    if (res < -0.5) res = val;
    else res = min(res, val);
}
 
// N <= 3
double sub1(
        int n, int maxDiv2, int target,
        const vector<tuple<int,int,int>>& edges,
        const vector<int>& node_types) {
    if (target == 0) {
        return 0.0;
    }
 
    double res = -1;
    vector<vector<double>> costs(n, vector<double> (n, -1));
    for (auto [u, v, cost] : edges) {
        costs[u][v] = costs[v][u] = cost;
    }
 
    // go directly from 0 -> target
    if (costs[0][target] >= 0)
        upMin(res, costs[0][target]);
    if (n <= 2) return res;
 
    // go 0 -> other vertex -> target
    int other = 3 - target;
    if (costs[0][other] >= 0 && costs[other][target] >= 0) {
        switch (node_types[other]) {
            case NORMAL:
                upMin(res, costs[0][other] + costs[other][target]);
                break;
            case ZERO:
                upMin(res, costs[other][target]);
                break;
            case DIV2:
                if (maxDiv2 >= 1) {
                    upMin(res, costs[0][other] / 2.0 + costs[other][target]);
                } else {
                    upMin(res, costs[0][other] + costs[other][target]);
                }
                break;
        }
    }
    return res;
}
 
// All nodes are NORMAL
double sub25(
        int n, int target,
        const vector<vector<pair<int,int>>>& g) {
    const int64_t INF = 1e18;
    vector<int64_t> dists(n, INF);
    set<pair<int64_t, int>> all;
    dists[0] = 0;
    all.insert({0LL, 0});
    while (!all.empty()) {
        auto [dist, u] = *all.begin();
        all.erase(all.begin());
        if (dist != dists[u]) continue;
 
        for (auto [v, cost] : g[u]) {
            int64_t cur = dist + cost;
            if (cur < dists[v]) {
                dists[v] = cur;
                all.insert({cur, v});
            }
        }
    }
    if (dists[target] == INF) dists[target] = -1;
    return dists[target];
}
 
// All nodes are NORMAL or ZERO
double sub36(
        int n, int target,
        const vector<vector<pair<int,int>>>& g,
        vector<int>& node_types) {
    // BFS to find all reachable ZERO nodes
    vector<bool> visited(n, false);
    queue<int> qu;
    qu.push(0);
    visited[0] = true;
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for (auto [v, _] : g[u]) {
            if (!visited[v] && v != target) {
                visited[v] = true;
                qu.push(v);
            }
        }
    }
 
    // Dijkstra from all reachable ZERO nodes
    const int64_t INF = 1e18;
    vector<int64_t> dists(n, INF);
    set<pair<int64_t, int>> all;
    node_types[0] = ZERO;
    for (int i = 0; i < n; ++i) {
        if (visited[i] && node_types[i] == ZERO) {
            dists[i] = 0;
            all.insert({0LL, i});
        }
    }
    while (!all.empty()) {
        auto [dist, u] = *all.begin();
        all.erase(all.begin());
        if (dist != dists[u]) continue;
 
        for (auto [v, cost] : g[u]) {
            int64_t cur = dist + cost;
            if (cur < dists[v]) {
                dists[v] = cur;
                all.insert({cur, v});
            }
        }
    }
    if (dists[target] == INF) dists[target] = -1;
    return dists[target];
}
 
double sub47(
        int n, int target, int maxDiv2,
        const vector<vector<pair<int,int>>>& g,
        vector<int>& node_types) {
    // BFS to find all reachable ZERO nodes
    vector<bool> visited(n, false);
    queue<int> qu;
    qu.push(0);
    visited[0] = true;
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for (auto [v, _] : g[u]) {
            if (!visited[v] && v != target) {
                visited[v] = true;
                qu.push(v);
            }
        }
    }
 
    // Dijkstra from all reachable ZERO nodes
    vector<double> dists(n, 1e18);
    vector<int> trace(n, -1);
    set<pair<double, int>> all;
    node_types[0] = ZERO;
    for (int i = 0; i < n; ++i) {
        if (visited[i] && node_types[i] == ZERO) {
            dists[i] = 0;
            trace[i] = i;
            all.insert({0.0, i});
        }
    }
 
    for (int div2 = 0; div2 <= maxDiv2; ++div2) {
        set<int> next_turn;
        vector<double> dist_next_turn(n, 1e18);
        while (!all.empty()) {
            auto [dist, u] = *all.begin();
            all.erase(all.begin());
            if (dist != dists[u]) continue;
            if (u == target) continue;  // must stop when reaching target node
 
            for (auto [v, cost] : g[u]) {
                double cur = dist + cost;
                if (cur < dists[v]) {
                    trace[v] = u;
                    dists[v] = cur;
                    all.insert({cur, v});
                }
                cur /= 2.0;
                if (node_types[v] == DIV2 && cur < dist_next_turn[v]) {
                    next_turn.insert(v);
                    dist_next_turn[v] = cur;
                }
            }
        }
 
        all.clear();
        for (int v : next_turn) {
            dists[v] = dist_next_turn[v];
            all.insert({dists[v], v});
        }
    }
    double res = dists[target];
    return (res > 1e17) ? -1 : res;
}
 
double sub8(
        int n, int target, int maxDiv2,
        const vector<vector<pair<int,int>>>& g,
        vector<int>& node_types) {
    maxDiv2 = min(maxDiv2, 70);
    return sub47(n, target, maxDiv2, g, node_types);
}
 
double solve(
        int n, int m, int maxDiv2, int target,
        vector<int> edge_froms,
        vector<int> edge_tos,
        vector<int> edge_costs,
        vector<int> node_types) {
 
    assert(m == SZ(edge_froms));
    assert(m == SZ(edge_tos));
    assert(m == SZ(edge_costs));
    assert(n == SZ(node_types));
 
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int u = edge_froms[i];
        int v = edge_tos[i];
        int cost = edge_costs[i];
 
        g[u].emplace_back(v, cost);
        g[v].emplace_back(u, cost);
    }
 
    return sub8(n, target, maxDiv2, g, node_types);
}
