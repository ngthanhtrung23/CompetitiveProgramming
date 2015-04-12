
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 100111;

int n, getIn[MN], getOut[MN], cur, father[20][MN], root, h[MN];
vector<int> ke[MN];

void init() {
    memset(father, 0, sizeof father);
    FOR(i,1,n) ke[i].clear();
    root = 1;
    cur = 0;
    h[1] = 1;
}

void dfs(int u, int fu) {
    getIn[u] = ++cur;
    father[0][u] = fu;

    for(int v : ke[u]) {
        if (v == fu) continue;

        h[v] = h[u] + 1;
        dfs(v, u);
    }
    getOut[u] = ++cur;
}

void initLCA() {
    FOR(t,1,19) {
        FOR(u,1,n) {
            father[t][u] = father[t-1][ father[t-1][u] ];
        }
    }
}

int lca(int u, int v) {
    if (u == v) return u;
    if (h[u] < h[v]) swap(u, v);
    if (h[u] > h[v]) {
        FORD(i,19,0) {
            int x = father[i][u];
            if (h[x] >= h[v]) u = x;
        }
    }
    if (u == v) return u;

    FORD(i,19,0)
        if (father[i][u] != father[i][v]) {
            u = father[i][u];
            v = father[i][v];
        }
    return father[0][u];
}

// u is ancestor of v ?
bool isAncestor(int u, int v) {
    if (u == v) return true;
    return getIn[u] < getIn[v] && getOut[v] < getOut[u];
}

int get(int u, int v) {
    if (isAncestor(v, u)) swap(u, v);
    if (isAncestor(u, v)) {
        int x = lca(v, root);
        if (isAncestor(u, x)) return x;
        else return u;
    }
    else {
        int l = lca(u, v);
        int x = lca(u, root);
        if (x != l && isAncestor(l, x)) return x;

        int y = lca(v, root);
        if (y != l && isAncestor(l, y)) return y;

        return l;
    }
}

int main() {
    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        init();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        dfs(1, -1);
        initLCA();
        int q; scanf("%d", &q);
        while (q--) {
            char typ; scanf("%c", &typ);
            while (typ != '?' && typ != '!') scanf("%c", &typ);
            assert(typ == '?' || typ == '!');
            if (typ == '?') {
                int u, v; scanf("%d%d", &u, &v);
                printf("%d\n", get(u, v));
            }
            else {
                int u; scanf("%d", &u);
                root = u;
            }
        }
    }
    return 0;
}
