#include "closing.h"
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using Graph = vector<vector<pair<int,ll>>>;
 
void dfs(int u, int fu, const Graph& g, vector<ll>& dists, vector<int>& trace) {
    for (auto [v, w] : g[u]) {
        if (v == fu) continue;
        assert(dists[v] < 0);
 
        dists[v] = dists[u] + w;
        trace[v] = u;
        dfs(v, u, g, dists, trace);
    }
}
 
pair<vector<ll>, vector<int>> get_dists(int u, const Graph& g) {
    int n = g.size();
    vector<ll> dists(n, -1);
    vector<int> trace(n, -1);
    dists[u] = 0;
 
    dfs(u, -1, g, dists, trace);
    return {dists, trace};
}
 
// subtask 1: cost(X, Y) > 2K
int subtask1(ll k, const vector<ll>& dx, const vector<ll>& dy) {
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
 
int sub9(int n, ll k, int x, int y,
        const vector<ll>& dx, const vector<ll>& dy,
        const vector<bool>& on_path) {
    int res = subtask1(k, dx, dy);
 
    // 0 .. [xl .. x .. xr]
    //               [yl .. y .. yr] .. n-1
    // Now we only consider the case where [xl, xr] and [yl, yr] overlap
    // They must overlap at least one point between [x, y]
    int cur = 0;
    vector<int> taken(n, 0);
    vector<Event> events;
    // 1. For every vertex not in path x -> y
    for (int i = 0; i < n; ++i) {
        if (on_path[i]) continue;
        ll a = min(dx[i], dy[i]);
        ll b = max(dx[i], dy[i]);
        if (b - a >= a) {
            events.push_back({a, i, 1});
            events.push_back({b - a, i, 1});
        } else {
            events.push_back({b, i, 2});
        }
    }
    // 2. On path x -> y, every point must be visited by either x or y
    for (int i = 0; i < n; ++i) {
        if (!on_path[i]) continue;
        k -= min(dx[i], dy[i]);
        // Additionally, we can choose to visit from other point
        ++cur;
        events.push_back({llabs(dx[i] - dy[i]), i, 1});
        taken[i] = 1;
    }
 
    if (k >= 0) {
        sort(events.begin(), events.end());
 
        multiset<pair<ll,int>> ones, twos;
        for (auto& event : events) {
            if (k >= event.cost) {
                k -= event.cost;
                cur += event.typ;
                taken[event.i] += event.typ;
                assert(taken[event.i] <= 2);

                if (event.typ == 1) ones.insert({event.cost, event.i});
            } else {
                if (event.typ == 2) twos.insert({event.cost, event.i});
            }

            // Swap 1 -> 2
            while (ones.size() > 0 && twos.size() > 0) {
                auto it_one = std::prev(ones.end());
                auto it_two = twos.begin();
                auto cost = it_two->first - it_one->first;
                if (cost <= k) {
                    k -= cost;
                    ++cur;
                    assert(taken[it_one->second] > 0);
                    taken[it_one->second]--;

                    assert(taken[it_two->second] == 0);
                    taken[it_two->second] = 2;

                    ones.erase(it_one);
                    twos.erase(it_two);
                } else break;
            }

            // break pair
            if (event.typ == 2 && !taken[event.i]) {
                auto cost = min(dx[event.i], dy[event.i]);
                if (cost <= k) {
                    k -= cost;
                    ++cur;
                    taken[event.i] = 1;
                    ones.insert({cost, event.i});
                    twos.erase({event.cost, event.i});
                }
            }
        }
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
 
    auto [distsX, traceX] = get_dists(X, g);
    auto [distsY, traceY] = get_dists(Y, g);
    vector<bool> on_path(n, false);
    int cur = Y;
    while (cur != X) {
        on_path[cur] = true;
        cur = traceX[cur];
    }
    on_path[X] = true;
    
    return sub9(n, K, X, Y, distsX, distsY, on_path);
}

