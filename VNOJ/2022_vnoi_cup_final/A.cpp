#include "bits/stdc++.h"
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, q; cin >> n >> m >> q;

    vector<vector<int>> g(n);
    while (m--) {
        int u, v; cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<int>> atDist(n + 1);
    int maxDist = 0;
    while (q--) {
        int c, d; cin >> c >> d;
        --c;
        atDist[d].push_back(c);
        maxDist = max(maxDist, d);
    }

    vector<bool> visited(n, false);
    vector<int> cur;
    for (int d = maxDist; d >= 1; d--) {
        for (int u : atDist[d]) if (!visited[u]) {
            cur.push_back(u);
            visited[u] = true;
        }
        if (d == 1) break;
        vector<int> next;

        for (int u : cur) {
            for (int v : g[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    next.push_back(v);
                }
            }
        }
        cur = std::move(next);
    }

    vector<int> greens;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) greens.push_back(i);
    }

    queue<int> qu;
    vector<int> dist(n, -1);
    for (int g : greens) {
        qu.push(g);
        dist[g] = 0;
    }
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for (int v : g[u]) {
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1;
                qu.push(v);
            }
        }
    }
    
    for (int d = 0; d <= maxDist; d++) {
        for (int u : atDist[d]) {
            if (dist[u] != d) {
                cout << "NO\n";
                return 0;
            }
        }
    }

    cout << "YES\n";
    cout << greens.size() << endl;
    for (int g : greens) cout << 1+g << ' ';
    cout << endl;
    return 0;
}
