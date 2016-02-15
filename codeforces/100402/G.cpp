
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

const int MN = 100111;
ll it[MN * 8];
struct Query {
    int l, r, x;
} a[MN];
bool operator < (const Query&a, const Query&b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}
int n, q;

const ll INF = 1000111000111000;
void build(int i, int l, int r) {
    it[i] = -INF;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);
}

void down(int i) {
    if (it[i] == -INF) return ;

    it[i<<1] = it[i];
    it[i<<1|1] = it[i];
    it[i] = -INF;
}

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i] = val;
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, v, val);
    update(i<<1|1, mid+1, r, u, v, val);
}

ll x[MN];

void go(int i, int l, int r) {
    if (l == r) {
        x[l] = it[i];
        if (x[l] == -INF) x[l] = 0;
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;

    go(i<<1, l, mid);
    go(i<<1|1, mid+1, r);
}

void build2(int i, int l, int r) {
    if (l == r) {
        it[i] = x[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build2(i<<1, l, mid);
    build2(i<<1|1, mid+1, r);

    it[i] = min(it[i<<1], it[i<<1|1]);
}
ll get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return INF;
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    return min(get(i<<1, l, mid, u, v), get(i<<1|1, mid+1, r, u, v));
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    while (cin >> n >> q) {
        FOR(i,1,q) cin >> a[i].l >> a[i].r >> a[i].x;
        sort(a+1, a+q+1);
        build(1, 1, n);

        FOR(i,1,q) {
            update(1, 1, n, a[i].l, a[i].r, a[i].x);
        }
        go(1, 1, n);

        build2(1, 1, n);
        bool ok = true;
        FOR(i,1,q) if (get(1, 1, n, a[i].l, a[i].r) != a[i].x) ok = false;

        if (ok) {
            puts("consistent");
            FOR(i,1,n) printf("%d ", (int) x[i]);
            puts("");
        }
        else puts("inconsistent");
    }
}
