#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 211;
int n, p;
int c[MN], sz[MN], nChild[MN];
vector<int> ke[MN];
int f[MN][MN][MN];
int trace[MN][MN][MN];
vector<int> children[MN];

bool marked[MN];

void dfs(int u, int fu) {
    sz[u] = 1;
    f[u][0][1] = c[u];
    int cur = 0;

    for (int v : ke[u]) {
        if (v == fu) continue;
        
        dfs(v, u);
        children[u].push_back(v);

        // DP
        ++cur;
        for (int ku = 0; ku <= sz[u]; ku++) {
            f[u][cur][ku] = f[u][cur - 1][ku];
            trace[u][cur][ku] = 0;
        }
        for (int ku = 0; ku <= sz[u]; ku++) {
            for (int kv = 0; kv <= sz[v]; kv++) {
                if (f[u][cur][ku + kv] < f[u][cur-1][ku] + f[v][nChild[v]][kv]) {
                    f[u][cur][ku + kv] = f[u][cur-1][ku]
                        + f[v][nChild[v]][kv];

                    trace[u][cur][ku + kv] = kv;
                }
            }
        }

        sz[u] += sz[v];
    }
    nChild[u] = cur;
    
    /*
    cout << "DP " << u << ": ";
    for (int i = 0; i <= sz[u]; i++) cout << f[u][cur][i] << ' ';
    cout << endl;
    */
}

void tr(int u, int fu, int required) {
    if (!required) return;

    marked[u] = true;

    for (int i = SZ(children[u]) - 1; i >= 0; i--) {
        int v = children[u][i];
        assert(v != fu);


        int kv = trace[u][i + 1][required];
        if (kv > 0) {
            tr(v, u, kv);
        }

        required -= kv;
    }
    assert(required == 1);
}

int32_t main() {
    ios::sync_with_stdio(0);
    while (cin >> n >> p) {
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
            ke[i].clear();
            children[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        memset(f, -0x3f, sizeof f);
        dfs(1, -1);

        pair<int,int> res = {-1000111000111000LL, -1};
        for (int i = 1; i <= n; i++) {
            res = max(res, {f[i][nChild[i]][p], i});
        }

        memset(marked, false, sizeof marked);
        tr(res.second, -1, p);
        int printed = 0;
        for (int i = 1; i <= n; i++) {
            if (marked[i]) {
                cout << i << ' ';
                ++printed;
            }
        }
        cout << endl;
        assert(printed == p);
        break;
    }
    return 0;
}

