#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a), _b=(b); i >= _b; --i)
#define REP(i,a) for(int i = 0, _a=(a); i < _a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

int n, f[2][111], m;
long double g[2][111];
long double cnt[111][111];
vector<int> ke[111];

void init() {
    FOR(i,1,n) {
        ke[i].clear();
        f[0][i] = f[1][i] = 111;
        g[0][i] = g[1][i] = 0;
    }
    f[0][1] = 0; f[1][n] = 0;
    g[0][1] = 1; g[1][n] = 1;
    memset(cnt, 0, sizeof cnt);
}

void inp() {
    cin >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        ke[u].PB(v); ke[v].PB(u);
    }
}

int qu[111];

void bfs(int u, int t) {
    int first = 1, last = 1;
    qu[1] = u;
    while (first <= last) {
        u = qu[first++];
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (f[t][v] > f[t][u] + 1) {
                f[t][v] = f[t][u] + 1;
                g[t][v] = g[t][u];
                qu[++last] = v;
            }
            else if (f[t][v] == f[t][u] + 1) {
                g[t][v] += g[t][u];
            }
        }
    }
}

void solve() {
    bfs(1, 0);
    bfs(n, 1);

    FOR(u,1,n) REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (f[0][u] + 1 + f[1][v] == f[0][n]) {
            cnt[u][v] = cnt[v][u] = g[0][u] * g[1][v];
        }
    }

    long double res = 0.0;
    FOR(i,1,n) {
        long double now = 0.0;
        FOR(j,1,n) now += cnt[i][j];
        res = max(res, now);
    }
    cout << (fixed) << setprecision(8) << res / g[0][n] << endl;
}

int main() {
    ios :: sync_with_stdio();
    while (cin >> n) {
        init();
        inp();
        solve();
    }
    return 0;
}
