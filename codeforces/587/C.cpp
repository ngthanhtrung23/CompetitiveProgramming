
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

#define index index__
const int MAXN = 100000 + 10;

struct Node {
    int nn[12];
    int sz;

    Node() { sz = 0; }

    void add(int x) {
        nn[sz++] = x;
        sort(nn, nn+sz);
        if (sz > 10) sz = 10;
    }
} empty;
int tmp[22];
void add(const Node& a, const Node& b, Node& res) {
    merge(a.nn, a.nn+a.sz,
            b.nn, b.nn+b.sz,
            tmp);
    int tmp_sz = a.sz + b.sz;
    tmp_sz = unique(tmp, tmp+tmp_sz) - tmp;

    res.sz = min(tmp_sz, 10);
    REP(i,res.sz)
        res.nn[i] = tmp[i];
}

vector<int> G[MAXN];
int sz[MAXN], dep[MAXN], fa[MAXN];
int dfn[MAXN], top[MAXN];
int n, m, index;

void dfs1(int u, int f = 0) {
    sz[u] = 1; fa[u] = f;
    for (auto &v: G[u]) if (v != f) {
        dep[v] = dep[u] + 1;
        dfs1(v, u); sz[u] += sz[v];
    }
}

void dfs2(int u, int chain, int f = 0) {
    int son(-1); dfn[u] = index ++; top[u] = chain;
    for (auto &v: G[u]) if (v != f) {
        if (son == -1 || sz[son] < sz[v]) son = v;
    }
    if (~son) dfs2(son, chain, u);
    for (auto &v: G[u]) if (v != f && v != son) {
        dfs2(v, v, u);
    }
}

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)
Node T[MAXN << 2];

void ins(int rt, int l, int r, int u, int val) {
    if (u < l || r < u) return ;

    T[rt].add(val);
    if (l == r) return ;

    ins(lson, l, mid, u, val);
    ins(rson, mid+1, r, u, val);
}

void ins(int u, int t) {
    ins(1, 1, n, dfn[u], t);
}

Node query(int rt, int l, int r, int u, int v) {
    if (v < l || r < u) return empty;
    if (u <= l && r <= v) return T[rt];

    Node res;
    add(query(lson, l, mid, u, v), query(rson, mid+1, r, u, v), res);
    return res;
}

Node query(int u, int v) {
    Node res;
    int fu = top[u], fv = top[v];
    while (fu != fv) {
        if (dep[fu] < dep[fv]) swap(u, v), swap(fu, fv);
        add(res, query(1, 1, n, dfn[fu], dfn[u]), res);
        u = fa[fu], fu = top[u];
    }
    if (dep[u] > dep[v]) swap(u, v);
    add(res, query(1, 1, n, dfn[u], dfn[v]), res);
    return res;
}

int main() {
    int q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n-1; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1);
    index = 0;
    dfs2(1, 1);

    FOR(i,1,n) ++dfn[i];

    FOR(i,1,m) {
        int x; scanf("%d", &x);
        ins(x, i);
    }
    while (q--) {
        int u, v, a; scanf("%d%d%d", &u, &v, &a);
        Node res = query(u, v);
        int t = min(res.sz, a);
        printf("%d", t);
        REP(i,t) printf(" %d", res.nn[i]);
        puts("");
    }
    return 0;
}
