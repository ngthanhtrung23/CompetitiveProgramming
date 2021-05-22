#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 1011;
vector<pair<int,int>> ke[MN];
int n;
int f[MN][2];

void dfs(int u) {
    f[u][0] = 0;
    if (ke[u].empty()) {
        f[u][1] = 1000111000111000LL;
    } else {
        f[u][1] = 0;
    }

    for (auto [v, c] : ke[u]) {
        dfs(v);

        f[u][0] += f[v][0];
        f[u][1] += min(f[v][1], f[v][0] + c);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            ke[i].clear();
        }

        for (int u = 2; u <= n; u++) {
            int pu, c; cin >> pu >> c;
            ke[pu].push_back({u, c});
        }

        if (n == 1) {
            cout << "0.00\n";
            continue;
        }

        dfs(1);
        cout << f[1][1] << ".00\n";
    }
    return 0;
}

