#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 10111;
const int MAX_COLOR = 10;
vector<int> ke[MN];
int f[MN][MAX_COLOR + 1];
int color[MN];

void dfs(int u, int fu) {
    for (int c = 1; c <= MAX_COLOR; c++) {
        f[u][c] = c;
    }

    for (int v : ke[u]) {
        if (v == fu) continue;

        dfs(v, u);

        for (int c = 1; c <= MAX_COLOR; c++) {
            int min_fv = 1000111000;
            for (int c2 = 1; c2 <= MAX_COLOR; c2++) {
                if (c != c2) {
                    min_fv = min(min_fv, f[v][c2]);
                }
            }

            f[u][c] += min_fv;
        }
    }
}

void trace(int u, int fu, int color_u) {
    color[u] = color_u;

    for (int v : ke[u]) {
        if (v == fu) continue;

        pair<int,int> min_fv = {1000111000, -1};
        for (int c = 1; c <= MAX_COLOR; c++) {
            if (c == color_u) continue;

            min_fv = min(min_fv, make_pair(f[v][c], c));
        }

        trace(v, u, min_fv.second);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) ke[i].clear();

        for (int i = 1; i < n; i++) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        dfs(1, -1);
        pair<int,int> res = {1000111000, -1};
        for (int c = 1; c <= MAX_COLOR; c++) {
            res = min(res, make_pair(f[1][c], c));
        }

        cout << res.first << '\n';
        trace(1, -1, res.second);

        for (int i = 1; i <= n; i++) {
            cout << color[i] << '\n';
        }
    }
    return 0;
}


