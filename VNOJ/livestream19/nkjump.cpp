#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

vector<vector<int>> edges;
vector<int> dp;

int f(int u) {
    if (dp[u] >= 0) {
        return dp[u];
    }

    int& res = dp[u];

    res = 1;
    for (int v : edges[u]) {
        res = max(res, 1 + f(v));
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    int n; cin >> n;
    vector<int> a(n);

    map<int, int> cnt;
    for (int& x : a) {
        cin >> x;
        cnt[x]++;
    }

    // build graph
    edges.resize(n);
    // edges[k] = list {i: i -> k}
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            int aj = a[k] - a[i];

            if (aj == a[i]) {
                if (cnt[aj] >= 2) edges[k].push_back(i);
            } else {
                if (cnt[aj] >= 1) edges[k].push_back(i);
            }
        }
    }

    // dp
    int res = 0;
    dp = vector<int> (n, -1);
    for (int i = 0; i < n; i++) {
        res = max(res, f(i));
    }
    cout << res << endl;
    return 0;
}
