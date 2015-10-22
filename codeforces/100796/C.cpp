#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;
int nMin, n;
vector<int> ke[MN];
ll g[MN];
int a[MN], sz[MN];

void dfs1(int u, int x) {
    if (ke[u].empty()) {
        sz[u] = 0;
        if (a[u] >= x) g[u] = 0;
        else g[u] = -MN;
        return;
    }

    g[u] = -MN;
    sz[u] = 1;

    ll allGood = 1;
    for(int v : ke[u]) {
        dfs1(v, x);
        sz[u] += sz[v];
        allGood += g[v];
    }
    g[u] = max(g[u], allGood);

    for(int v : ke[u]) {
        g[u] = max(g[u], sz[u] - 1 - sz[v] + g[v]);
    }
}

void dfs2(int u, int x) {
    if (ke[u].empty()) {
        if (a[u] <= x) g[u] = 0;
        else g[u] = -MN;
        return ;
    }

    g[u] = -MN;

    ll allGood = 1;
    for(int v : ke[u]) {
        dfs2(v, x);
        allGood += g[v];
    }
    g[u] = max(g[u], allGood);

    for(int v : ke[u]) {
        g[u] = max(g[u], sz[u] - 1 - sz[v] + g[v]);
    }
}

int getMax() {
    int l = 0, r = 1e9, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        
        dfs1(1, mid);
        if (g[1] >= nMin) {
            res = mid;
            l = mid + 1;
        } else r = mid - 1;
    }

    dfs1(1, 3);
//    PR(g, n);
    return res;
}

int getMin() {
    int l = 0, r = 1e9, res = 1e9;
    int nMax = sz[1] - nMin;
    while (l <= r) {
        int mid = (l + r) >> 1;
        dfs2(1, mid);
        if (g[1] >= nMax) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &nMin) == 2) {
        FOR(i,1,n) ke[i].clear();
        FOR(u,2,n) {
            int v; scanf("%d", &v);
            ke[v].push_back(u);
        }
        FOR(i,1,n) scanf("%d", &a[i]);
        cout << getMin() << ' ' << getMax() << endl;
    }
}