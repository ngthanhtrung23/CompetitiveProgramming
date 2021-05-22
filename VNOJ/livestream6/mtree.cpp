#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 100111;
const int MOD = 1e9 + 7;

int n;
vector< pair<int,int> > ke[MN];
int f[MN];
int inv2 = 500000004;
int res = 0;

void dfs(int u, int fu) {
    f[u] = 0;
    int sum_xv2 = 0;

    for (auto [v, c] : ke[u]) {
        if (v == fu) continue;

        dfs(v, u);

        int xv = c * (f[v] + 1) % MOD;
        f[u] = (f[u] + xv) % MOD;

        sum_xv2 = (sum_xv2 + xv * xv) % MOD;
    }

    int g = (f[u] * f[u] % MOD - sum_xv2 + MOD) * inv2 % MOD;
    res = (res + f[u] + g) % MOD;
}

int32_t main() {
    ios::sync_with_stdio(0);
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            ke[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v, c; cin >> u >> v >> c;

            ke[u].push_back({v, c});
            ke[v].push_back({u, c});
        }

        res = 0;
        dfs(1, -1);
        cout << res << endl;
    }
    return 0;
}

