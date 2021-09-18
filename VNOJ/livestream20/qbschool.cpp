#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 5011;

// d[i] = shortest path to i
// cnt[i] = number of shortest path to i
int d[MN], cnt[MN];

vector< pair<int, int> > edges[MN]; // (v, cost)

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int dir; cin >> dir;
        int u, v, cost; cin >> u >> v >> cost;

        if (dir == 1) {
            edges[u].push_back({v, cost});
        } else {
            edges[u].push_back({v, cost});
            edges[v].push_back({u, cost});
        }
    }

    // init
    memset(cnt, 0, sizeof cnt);
    memset(d, 0x3f, sizeof d);

    d[1] = 0;
    cnt[1] = 1;
    set< pair<int, int> > all;  // (len, u)
    all.insert({0, 1});

    // dijkstra
    while (!all.empty()) {
        auto [len, u] = *all.begin();
        all.erase(all.begin());

        if (len != d[u]) continue;

        for (auto [v, cost] : edges[u]) {
            int cur = d[u] + cost;

            if (cur == d[v]) {
                cnt[v] += cnt[u];
            } else if (cur < d[v]) {
                d[v] = cur;
                cnt[v] = cnt[u];
                all.insert({d[v], v});
            }
        }
    }

    // 
    cout << d[n] << ' ' << cnt[n] << endl;
    return 0;
}
