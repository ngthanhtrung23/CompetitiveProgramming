#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 411;
int n;
int f[MN];
vector<int> ke[MN];

void dfs(int u) {
    vector<int> cur;
    for (int v : ke[u]) {
        dfs(v);
        cur.push_back(f[v]);
    }

    sort(cur.begin(), cur.end(), greater<int>());
    int stones_on_children = 0;
    f[u] = 1;

    for (int x : cur) {
        f[u] = max(f[u], x + stones_on_children);
        stones_on_children++;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin >> n;
    int u;
    while (cin >> u) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int v; cin >> v;
            ke[u].push_back(v);
        }
    }
    dfs(1);
    cout << f[1] << endl;
    return 0;
}

