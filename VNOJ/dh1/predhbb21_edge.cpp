#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 200111;
vector<int> ke[MN];
int low[MN], num[MN], sz[MN];
int cur;
int n, m;
int res = 0;
int connectedComponents;
set< pair<int,int> > all;
int cntBridge = 0;

void dfs(int u) {
    num[u] = ++cur;
    low[u] = num[u];
    sz[u] = 1;

    for (int v : ke[u]) {
        if (all.count({u, v})) continue;
        all.insert({u, v});
        all.insert({v, u});

        if (num[v]) {
            low[u] = min(low[u], num[v]);
        } else {
            dfs(v);
            low[u] = min(low[u], low[v]);
            sz[u] += sz[v];
        }

        // delete edge (u, v)
        // bridge
        if (low[v] > num[u]) {
            ++cntBridge;
            res += sz[v] * (n - sz[v]) - 1;
            // cout << "bridge: " << u << ' ' << v << ' ' << res << endl;
        } else {
            // not bridge
            res += n * (n - 1) / 2 - m;
            // cout << "not br: " << u << ' ' << v << ' ' << res << endl;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    // init
    for (int i = 1; i <= n; i++) {
        ke[i].clear();
    }
    memset(low, 0, sizeof low);
    memset(num, 0, sizeof num);
    connectedComponents = 0;
    all.clear();

    // input
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }

    // solve
    vector<int> roots;
    res = 0;
    cur = 0;
    all.clear();
    cntBridge = 0;
    for (int i = 1; i <= n; i++) {
        if (num[i]) continue;

        cur = 0;
        roots.push_back(i);
        dfs(i);
    }

    // cout << "num = "; for (int i = 1; i <= n; i++) cout << num[i] << ' '; cout << endl;
    // cout << "low = "; for (int i = 1; i <= n; i++) cout << low[i] << ' '; cout << endl;

    if (roots.size() > 2) {
        cout << 0 << endl;
        return 0;
    }
    if (roots.size() == 2) {
        cout << (m - cntBridge) * sz[roots[0]] * sz[roots[1]] << endl;
        return 0;
    }
    cout << res << endl;
    return 0;
}
