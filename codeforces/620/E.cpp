
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 400111;

struct Node {
    ll sum;
    ll lazy;
} it[MN * 8];

void down(int i) {
    if (it[i].lazy) {
        ll t = it[i].lazy;
        it[i].lazy = 0;

        it[i*2].sum = t;
        it[i*2].lazy = t;

        it[i*2 + 1].sum = t;
        it[i*2 + 1].lazy = t;
    }
}

void update(int i, int l, int r, int u, int v, ll val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].sum = val;
        it[i].lazy = val;
        return ;
    }
    int mid = (l + r) >> 1;
    down(i);

    update(i*2, l, mid, u, v, val);
    update(i*2+1, mid+1, r, u, v, val);

    it[i].sum = it[i*2].sum | it[i*2 + 1].sum;
}

ll get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum;

    down(i);

    int mid = (l + r) >> 1;
    return get(i*2, l, mid, u, v) | get(i*2 + 1, mid+1, r, u, v);
}

int n, q, color[MN], getIn[MN], getOut[MN], dfs1Num;
vector<int> ke[MN];

void dfs1(int u, int fu) {
    getIn[u] = ++dfs1Num;
    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs1(v, u);
    }
    getOut[u] = dfs1Num;
}

void dfs2(int u, int fu) {
    update(1, 1, n, getIn[u], getOut[u], 1LL << color[u]);

    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs2(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) scanf("%d", &color[i]);
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        dfs1Num = 0;
        dfs1(1, -1);
//        PR(getIn, n);
//        PR(getOut, n);

        memset(it, 0, sizeof it);
        dfs2(1, -1);

        while (q--) {
            int typ; scanf("%d", &typ);
            if (typ == 1) {
                int u, c; scanf("%d%d", &u, &c);
                update(1, 1, n, getIn[u], getOut[u], 1LL << c);
            }
            else {
                int u; scanf("%d", &u);
                ll res = get(1, 1, n, getIn[u], getOut[u]);
                printf("%d\n", __builtin_popcountll(res));
            }
        }
    }
}
