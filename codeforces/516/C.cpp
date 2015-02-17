#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 100111;
const ll oo = 1000111000111000111LL;

struct Node {
    ll from, to, all;
    ll sumd;
} it[MN * 8];

ll h[MN], d[MN];
int n, q;

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

Node combine(const Node& a, const Node& b) {
    Node res;
    res.sumd = a.sumd + b.sumd;
    res.from = max(a.from + b.sumd, b.from);
    res.to   = max(a.to, a.sumd + b.to);
    res.all  = max(max(a.all, b.all), a.from + b.to);
    return res;
}

void build(int i, int l, int r) {
    if (l == r) {
        it[i].sumd = d[l];
        it[i].from = (h[l] << 1) + d[l];
        it[i].to   = (h[l] << 1);
        it[i].all  = -oo;
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
    it[i] = combine(it[CT(i)], it[CP(i)]);
}

Node f[100111];
int nf;

void visit(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return;
    if (u <= l && r <= v) {
        f[++nf] = it[i];
        return ;
    }
    int mid = (l + r) >> 1;
    visit(CT(i), l, mid, u, v);
    visit(CP(i), mid+1, r, u, v);
}

ll query(int u, int v) {
    nf = 0;
    if (u <= v) {
        visit(1, 1, n, v+1, n);
        visit(1, 1, n, 1, u-1);
    }
    else {
        visit(1, 1, n, v+1, u-1);
    }

    ll res = 0;
    FOR(i,1,nf) res = max(res, f[i].all);
    
    ll from = -oo;
    FOR(i,1,nf) {
        if (i >= 2) {
            res = max(res, from + f[i].to);
        }
        from = max(from + f[i].sumd, f[i].from);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(0);
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) scanf("%d", &d[i]);
        FOR(i,1,n) scanf("%d", &h[i]);

        build(1, 1, n);
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            printf("%I64d\n", query(u, v));
        }
    }
    return 0;
}
