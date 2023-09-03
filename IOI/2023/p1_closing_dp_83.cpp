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

ll f[3011][6011];
void upMin(ll& f, ll val) {
    if (val < f) f = val;
}

// N <= 3000
int sub8(int n, ll k,
        const vector<ll>& dx, const vector<ll>& dy,
        const vector<bool>& on_path) {
    int res = subtask1(k, dx, dy);

    if (n <= 3000) {
        memset(f, 0x7f, sizeof f);
        f[0][0] = 0;
        for (int i = 0; i < n; ++i) {
            if (on_path[i]) {
                for (int j = 0; j <= 2*i; ++j) {
                    upMin(f[i+1][j+1], f[i][j] + min(dx[i], dy[i]));
                    upMin(f[i+1][j+2], f[i][j] + max(dx[i], dy[i]));
                }
            } else {
                for (int j = 0; j <= 2*i; ++j) {
                    f[i+1][j] = min(f[i+1][j], f[i][j]);
                    upMin(f[i+1][j+1], f[i][j] + min(dx[i], dy[i]));
                    upMin(f[i+1][j+2], f[i][j] + max(dx[i], dy[i]));
                }
            }
        }
        for (int j = 0; j <= 2*n; ++j) {
            if (f[n][j] <= k) res = max(res, j);
        }
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
    
    return sub8(n, K, distsX, distsY, on_path);
}
