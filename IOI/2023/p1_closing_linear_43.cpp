#include "closing.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Graph = vector<vector<pair<int,ll>>>;

void dfs(int u, int fu, const Graph& g, vector<ll>& dists) {
    for (auto [v, w] : g[u]) {
        if (v == fu) continue;
        assert(dists[v] < 0);

        dists[v] = dists[u] + w;
        dfs(v, u, g, dists);
    }
}

vector<ll> get_dists(int u, const Graph& g) {
    int n = g.size();
    vector<ll> dists(n, -1);
    dists[u] = 0;

    dfs(u, -1, g, dists);
    return dists;
}

int no_common(ll k, const vector<ll>& dx, const vector<ll>& dy) {
    vector<ll> all;
    for (auto d : dx) all.push_back(d);
    for (auto d : dy) all.push_back(d);
    sort(all.begin(), all.end());
    int cnt = 0;
    for (auto d : all) {
        if (d <= k) {
            k -= d;
            ++cnt;
        } else break;
    }
    return cnt;
}

// linear graph
struct Event {
    ll cost;
    int i;
    int typ;  // 1 = SINGLE, 2 = PAIR
};
bool operator < (const Event& a, const Event& b) {
    return a.cost * (3 - a.typ) < b.cost * (3 - b.typ);
}

int sub4(int n, ll k, int x, int y,
        const vector<ll>& dx, const vector<ll>& dy) { // x < y
    int res = no_common(k, dx, dy);
    // 0 .. [xl .. x .. xr]
    //               [yl .. y .. yr] .. n-1
    // Now we only consider the case where [xl, xr] and [yl, yr] overlap
    // They must overlap at least one point between [x, y]
    int cur = 0;
    vector<Event> events;
    // 1. In [0, x], every point can be visited by x then y
    for (int i = 0; i < x; ++i) {
        if (dy[i] - dx[i] >= dx[i]) {
            events.push_back({dx[i], i, 1});
            events.push_back({dy[i] - dx[i], i, 1});
        } else {
            // When dy[i] - dx[i] < dx[i], if we sort normally, we will
            // choose (dy[i] - dx[i]) before dx[i], which is wrong
            // -> we must "bundle" these together
            events.push_back({dy[i], i, 2});
        }
    }
    // 2. In [x, y], every point must be visited by either x or y
    for (int i = x; i <= y; ++i) {
        k -= min(dx[i], dy[i]);
        // Additionally, we can choose to visit from other point
        ++cur;
        events.push_back({llabs(dx[i] - dy[i]), i, 1});
    }
    // 3. In [y, n-1]: same as (1) {{{
    for (int i = y+1; i < n; ++i) {
        if (dx[i] - dy[i] >= dy[i]) {
            events.push_back({dy[i], i, 1});
            events.push_back({dx[i] - dy[i], i, 1});
        } else {
            events.push_back({dx[i], i, 2});
        }
    }
    // }}}

    if (k >= 0) {
        sort(events.begin(), events.end());
        for (auto& event : events) {
            if (event.cost > k) break;
            k -= event.cost;
            cur += event.typ;
            event.typ = 0;
        }
        // Break "bundle"
        set<ll> costs;
        for (auto& event : events)
            if (event.typ == 2) costs.insert(min(dx[event.i], dy[event.i]));
        for (auto cost : costs) if (k >= cost) k -= cost, ++cur;
        res = max(res, cur);
    }
    return res;
}

int max_score(int n, int X, int Y, long long K,
              vector<int> U, vector<int> V, vector<int> W) {
    Graph g(n);
    assert(int(U.size()) == n-1);
    assert(int(V.size()) == n-1);
    assert(int(W.size()) == n-1);
    for (int i = 0; i < n - 1; i++) {
        int u = U[i];
        int v = V[i];
        int w = W[i];
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    if (X > Y) swap(X, Y);

    auto distsX = get_dists(X, g);
    auto distsY = get_dists(Y, g);
    
    return sub4(n, K, X, Y, distsX, distsY);
}

