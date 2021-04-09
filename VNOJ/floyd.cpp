#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    int n, m, q;
    while (cin >> n >> m >> q) {
        vector< vector< pair<int,int> > > adj(n);

        while (m--) {
            int u, v, c; cin >> u >> v >> c;
            u--;
            v--;

            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        }

        // dijkstra
        vector< vector<int> > f(n);
        vector< vector<int> > trace(n);
        for (int i = 0; i < n; i++) {
            f[i] = vector<int> (n, 1000111000);
            trace[i].resize(n);

            set< pair<int, int> > all;
            all.insert({0, i});
            f[i][i] = 0;
            trace[i][i] = -1;

            while (!all.empty()) {
                auto [fu, u] = *all.begin();
                all.erase(all.begin());

                if (f[i][u] != fu) continue;

                for (auto [v, c] : adj[u]) {
                    if (f[i][v] > f[i][u] + c) {
                        f[i][v] = f[i][u] + c;
                        trace[i][v] = u;

                        all.insert({f[i][v], v});
                    }
                }
            }
        }

        // queries
        while (q--) {
            int typ, u, v; cin >> typ >> u >> v;
            --u;
            --v;

            if (typ == 0) {
                cout << f[u][v] << '\n';
            } else {
                assert(typ == 1);

                vector<int> res;
                while (v != u) {
                    res.push_back(v);
                    v = trace[u][v];
                }
                res.push_back(u);
                reverse(res.begin(), res.end());
                cout << res.size();
                for (int x : res) cout << ' ' << x + 1;
                cout << '\n';
            }
        }
    }
    return 0;
}
