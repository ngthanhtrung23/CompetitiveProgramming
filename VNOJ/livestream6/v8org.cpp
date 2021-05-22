#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 10111;

vector<int> ke[MN];
int res;
int n, k;

int dfs(int u) {
    int sz = 1;

    for (int v : ke[u]) {
        sz += dfs(v);
    }

    if (sz >= k) {
        res++;
        sz = 0;
    }

    return sz;
}

int32_t main() {
    ios::sync_with_stdio(0);
    while (cin >> k >> n) {
        for (int i = 1; i <= n; i++) {
            ke[i].clear();
        }
        for (int i = 2; i <= n; i++) {
            int pi; cin >> pi;
            ke[pi].push_back(i);
        }
        res = 0;
        dfs(1);
        cout << res << endl;
    }
    return 0;
}

