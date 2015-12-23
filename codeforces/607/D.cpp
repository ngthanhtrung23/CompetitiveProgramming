
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

const ll MOD = 1e9 + 7;
const int MN = 400111;

int getIn[MN], getOut[MN], n, dfsNum;
vector<int> ke[MN];
int a[MN];

struct Query {
    int u, v;
    int typ;

    void read() {
        scanf("%d", &typ);
        if (typ == 1) {
            ++n;
            scanf("%d", &u); v = n;
            scanf("%d", &a[v]);

            ke[u].push_back(v);
        }
        else {
            scanf("%d", &u);
        }
    }
} queries[MN];

void dfs(int u) {
    getIn[u] = ++dfsNum;
    for(int v : ke[u]) {
        dfs(v);
    }
    getOut[u] = ++dfsNum;
}

ll power(ll x, ll k) {
    ll res = 1;
    while (k > 0) {
        if (k & 1) res = res * x % MOD;
        x = x * x % MOD;
        k >>= 1;
    }
    return res;
}

ll inverse(ll x) {
    return power(x, MOD - 2);
}

struct Node {
    ll mult;
    ll sum;
    ll lazy;
} it[MN * 4];

void updateMult(int i, int l, int r, int u, ll delta) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].mult = it[i].mult * delta % MOD;
        return ;
    }
    int mid = (l + r) >> 1;
    updateMult(i<<1, l, mid, u, delta);
    updateMult(i<<1|1, mid+1, r, u, delta);

    it[i].mult = it[i<<1].mult * it[i<<1|1].mult % MOD;
}
ll getMult(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 1ll;
    if (u <= l && r <= v) {
        return it[i].mult;
    }
    int mid = (l + r) >> 1;

    return getMult(i<<1, l, mid, u, v) * getMult(i<<1|1, mid+1, r, u, v) % MOD;
}

void up(int i) {
    it[i].sum = (it[i<<1].sum + it[i<<1|1].sum) % MOD;
}

void down(int i) {
    if (it[i].lazy > 1) {
        ll t = it[i].lazy;
        it[i].lazy = 1;

        it[i<<1].lazy = it[i<<1].lazy * t % MOD;
        it[i<<1].sum  = it[i<<1].sum  * t % MOD;

        it[i<<1|1].lazy = it[i<<1|1].lazy * t % MOD;
        it[i<<1|1].sum  = it[i<<1|1].sum  * t % MOD;
    }
}

void multiply(int i, int l, int r, int u, int v, ll val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].lazy = (it[i].lazy * val) % MOD;
        it[i].sum = (it[i].sum * val) % MOD;
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;
    multiply(i<<1, l, mid, u, v, val);
    multiply(i<<1|1, mid+1, r, u, v, val);
    up(i);
}
void update(int i, int l, int r, int u, ll val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].sum = (it[i].sum + val) % MOD;
        return ;
    }
    down(i);

    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, val);
    update(i<<1|1, mid+1, r, u, val);

    up(i);
}
ll get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum;

    down(i);
    int mid = (l + r) >> 1;
    ll res = (get(i<<1, l, mid, u, v) + get(i<<1|1, mid+1, r, u, v)) % MOD;
    up(i);

    return res;
}
int sz[MN];

void build(int i, int l, int r) {
    it[i].sum = 0;
    it[i].mult = 1;
    it[i].lazy = 1;
    if (l == r) return ;

    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int q;
    while (scanf("%d%d", &a[1], &q) == 2) {
        FOR(i,1,q) ke[i].clear();

        n = 1;
        FOR(i,1,q) {
            queries[i].read();
        }
        dfsNum = 0;
        dfs(1);

//        PR(getIn, n);
//        PR(getOut, n);
//        PR(a, n);

        n *= 2;
        build(1, 1, n);
        sz[1] = 1;
        update(1, 1, n, getIn[1], a[1]);

        FOR(i,1,q) {
            if (queries[i].typ == 1) {
                int u = queries[i].u;
                int v = queries[i].v;
                ll mult1 = getMult(1, 1, n, 1, getIn[u]);

                sz[v] = 1;

                updateMult(1, 1, n, getIn[u], inverse(sz[u]) * (sz[u] + 1) % MOD);
                updateMult(1, 1, n, getOut[u], sz[u] * inverse(sz[u] + 1) % MOD);
                sz[u] += 1;

                ll mult = getMult(1, 1, n, 1, getIn[v]);

                ll mult2 = getMult(1, 1, n, 1, getIn[u]);
                multiply(1, 1, n, getIn[u], getOut[u], inverse(mult1) * mult2 % MOD);

                update(1, 1, n, getIn[v], (mult * a[v]) % MOD);
            }
            else {
                int u = queries[i].u;
                ll sum = get(1, 1, n, getIn[u], getOut[u]);
                ll mult = getMult(1, 1, n, 1, getIn[u] - 1);
                sum = sum * inverse(mult) % MOD;
                printf("%d\n", (int) sum);
            }
        }
    }
}
