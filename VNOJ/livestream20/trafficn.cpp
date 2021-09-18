// (u, 0): chua di qua k canh
// (u, 1): da di qua k canh

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

void solve() {
    int n, nEdges, nAdd, start, target;
    cin >> n >> nEdges >> nAdd >> start >> target;

    vector< vector< pair<int, int> > > edges(n + 1);
    vector< vector< pair<int, int> > > addEdges(n + 1);

    while (nEdges--) {
        int u, v, cost; cin >> u >> v >> cost;
        edges[u].emplace_back(v, cost);
    }

    while (nAdd--) {
        int u, v, cost; cin >> u >> v >> cost;
        addEdges[u].emplace_back(v, cost);
        addEdges[v].emplace_back(u, cost);
    }

    // dijkstra
    vector<int> d[2] = {
        vector<int> (n+1, 1e15),
        vector<int> (n+1, 1e15)
    };
    set< tuple<int,int,int> > all;
    d[0][start] = 0;
    all.insert({0, 0, start});

    while (!all.empty()) {
        auto [du, passed, u] = *all.begin();
        all.erase(all.begin());

        if (du != d[passed][u]) continue;
        if (u == target) {
            cout << du << endl;
            return;
        }

        // edges
        // (0, u) -> (0, v)
        // (1, u) -> (1, v)
        for (auto [v, cost] : edges[u]) {
            if (d[passed][v] > du + cost) {
                d[passed][v] = du + cost;
                all.insert({d[passed][v], passed, v});
            }
        }

        // addEdges
        // (0, u) -> (1, v)
        if (passed == 0) {
            for (auto [v, cost] : addEdges[u]) {
                if (d[1][v] > du + cost) {
                    d[1][v] = du + cost;
                    all.insert({d[1][v], 1, v});
                }
            }
        }
    }

    cout << -1 << endl;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        solve();
    }
    return 0;
}
