#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const long double PI = acos((long double) -1.0);

const int MN = 200111;

int n, f[MN], g[MN], sz[MN];
vector< pair<int,int> > ke[MN];

void dfs1(int u, int fu) {
    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;

        if (ke[u][i].S == 1) ++f[u];
        ++sz[u];
        dfs1(v, u);

        sz[u] += sz[v];
        f[u] += f[v];
    }
}

void dfs2(int u, int fu, int pre) {
    if (u == 1) g[u] = 0;
    else {
        if (pre == -1) ++g[u];
        g[u] += g[fu] + f[fu];

        // Remove edges in subtree u
        if (pre == 1) --g[u];
        g[u] -= f[u];
    }
    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;

        dfs2(v, u, ke[u][i].S);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(MP(v,1));
            ke[v].PB(MP(u,-1));
        }

        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        memset(sz, 0, sizeof sz);

        dfs1(1, -1);
        dfs2(1, -1, -1);

        int res = n-1;
        FOR(i,1,n) {
            res = min(res, n - 1 - f[i] - g[i]);
        }
        printf("%d\n", res);
        FOR(i,1,n) if (res == n - 1 - f[i] - g[i]) {
            printf("%d ", i);
        }
        puts("");
    }
    return 0;
}