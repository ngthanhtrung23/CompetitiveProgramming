// graph:
// - vertex: (u, remaining cost)
//   - currently at u
//
// - edges:
//   - (u, remaining) -> (v, remaining - cost(u, v))
//
// (1, K) -> (2, K - 3) -> (4, K - 6)
//        -> (3, K - 1)

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 111;
const int MC = 10111;

int d[MN][MC]; // (u, remaining cost)

void solve() {
    // input
    int K, n, nEdges;
    cin >> K >> n >> nEdges;

    vector<vector< tuple<int, int, int> > > edges(n + 1);

    while (nEdges--) {
        int u, v, len, cost;
        cin >> u >> v >> len >> cost;

        edges[u].push_back({v, len, cost});
    }

    // dijkstra
    memset(d, 0x3f, sizeof d);
    d[1][K] = 0;
    set< tuple<int,int,int> > all;
    all.insert({0, 1, K});

    while (!all.empty()) {
        auto [du, u, remaining] = *all.begin();
        all.erase(all.begin());

        if (du != d[u][remaining]) continue;
        if (u == n) {
            cout << du << '\n';
            return;
        }

        for (auto [v, len, cost] : edges[u]) {
            // (u, remaining) -> (v, remaining - cost)
            if (remaining < cost) continue;

            int cur = d[u][remaining] + len;
            if (d[v][remaining - cost] > cur) {
                d[v][remaining - cost] = cur;
                all.insert({cur, v, remaining - cost});
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
