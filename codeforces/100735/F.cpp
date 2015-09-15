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
const int INF = 1e9;

int A, B, n, q;
ll a[2][MN];


struct Node {
    int cnt, first_id;

    int hasSet[2];
    ll inc[2], all[2];
    pair<ll,int> nn[2], ln[2];
    ll sum[2];
    ll sum_prod;

    void remove() {
        cnt = 0;
        first_id = -1;
        REP(t,2) {
            hasSet[t] = 0;
            inc[t] = all[t] = 0;
            nn[t] = make_pair(INF, -1);
            ln[t] = make_pair(-INF, -1);
            sum[t] = 0;
        }
        sum_prod = 0;
    }

    void setValue(int t, ll val) {
        if (cnt == 0) return ;
        // cnt, first_id : no change
        hasSet[t] = 1;
        all[t] = val;
        inc[t] = 0;

        nn[t] = ln[t] = make_pair(val, first_id);
        sum[t] = cnt * val;

        if (hasSet[1-t]) sum_prod = cnt * (ll) (all[0] + inc[0]) * (ll) (all[1] + inc[1]);
        else             sum_prod = sum[1-t] * (all[t] + inc[t]);
    }

    void increase(int t, ll val) {
        if (cnt == 0) return ;
        // cnt, first_id : no change
        // hasSet[t], all[t] : no change
        inc[t] += val;
        nn[t].first += val;
        ln[t].first += val;
        sum[t] += val * cnt;

        sum_prod += val * sum[1-t];
    }
} it[MN * 4], empty;

Node operator + (const Node& left, const Node& right) {
    Node res;
    res.cnt = left.cnt + right.cnt;
    res.first_id = (left.first_id == -1) ? right.first_id : left.first_id;

    REP(t,2) {
        res.hasSet[t] = 0;
        res.all[t] = 0;
        res.inc[t] = 0;

        res.nn[t] = min(left.nn[t], right.nn[t]);
        res.ln[t] = max(left.ln[t], right.ln[t]);

        res.sum[t] = left.sum[t] + right.sum[t];
    }
    res.sum_prod = left.sum_prod + right.sum_prod;
    return res;
}

void buildTree(int i, int l, int r) {
    if (l == r) {
        it[i].cnt = 1;
        it[i].first_id = l;
        REP(t,2) {
            it[i].hasSet[t] = it[i].all[t] = it[i].inc[t] = 0;
            it[i].nn[t] = it[i].ln[t] = make_pair(a[t][l], l);
            it[i].sum[t] = a[t][l];
        }
        it[i].sum_prod = a[0][l] * (ll) a[1][l];
        return ;
    }
    int mid = (l + r) >> 1;
    buildTree(i<<1  , l, mid);
    buildTree(i<<1|1, mid+1, r);

    it[i] = it[i<<1] + it[i<<1|1];
}

void down(int i, int l, int r, int mid) {
    REP(t,2) {
        if (it[i].hasSet[t]) {
            it[i<<1  ].setValue(t, it[i].all[t]);
            it[i<<1|1].setValue(t, it[i].all[t]);

            it[i].hasSet[t] = 0;
            it[i].all[t] = 0;
        }
        if (it[i].inc[t]) {
            it[i<<1  ].increase(t, it[i].inc[t]);
            it[i<<1|1].increase(t, it[i].inc[t]);
            it[i].inc[t] = 0;
        }
    }
}

void remove(int i, int l, int r, int u) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].remove();
        return ;
    }
    int mid = (l + r) >> 1;

    down(i, l, r, mid);

    remove(i<<1  , l, mid, u);
    remove(i<<1|1, mid+1, r, u);

    it[i] = it[i<<1] + it[i<<1|1];
}

void setValue(int i, int l, int r, int t, int u, int v, ll val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].setValue(t, val);
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    setValue(i<<1  , l, mid, t, u, v, val);
    setValue(i<<1|1, mid+1, r, t, u, v, val);

    it[i] = it[i<<1] + it[i<<1|1];
}

void increase(int i, int l, int r, int t, int u, int v, ll val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].increase(t, val);
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    increase(i<<1  , l, mid, t, u, v, val);
    increase(i<<1|1, mid+1, r, t, u, v, val);

    it[i] = it[i<<1] + it[i<<1|1];
}

Node get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return empty;
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    return get(i<<1, l, mid, u, v) + get(i<<1|1, mid+1, r, u, v);
}

void cleanTree(int t) {
    int X = (t == 0) ? A : B;
    while (it[1].cnt && it[1].nn[t].first < 0) remove(1, 1, n, it[1].nn[t].second);
    while (it[1].cnt && it[1].ln[t].first > X) remove(1, 1, n, it[1].ln[t].second);
}

void setValue(int t, int u, int v, int val) {
    setValue(1, 1, n, t, u, v, val);
    cleanTree(t);
}

void increase(int t, int u, int v, int val) {
    increase(1, 1, n, t, u, v, val);
    cleanTree(t);
}

struct Query {
    int typ, l, r, v;

    void read() {
        scanf("%d", &typ);
        if (typ <= 4) scanf("%d%d%d", &l, &r, &v);
        else scanf("%d%d", &l, &r);
    }

    void process() {
        if (typ == 1) setValue(0, l, r, v);
        if (typ == 2) setValue(1, l, r, v);
        if (typ == 3) increase(0, l, r, v);
        if (typ == 4) increase(1, l, r, v);
        if (typ == 5 || typ == 6) {
            Node res = get(1, 1, n, l, r);

            if (res.cnt == 0) puts("0");
            else {
                if (typ == 5) printf("%I64d\n", res.sum_prod);
                else printf("%d\n", res.cnt);
            }
        }
    }
} queries[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) {
            int x, y;
            scanf("%d%d", &x, &y);
            a[0][i] = x;
            a[1][i] = y;
        }
        memset(it, 0, sizeof it);

//        PR(a[0], n);
//        PR(a[1], n);

        FOR(i,1,q) queries[i].read();
        scanf("%d%d", &A, &B);

        buildTree(1, 1, n);

        cleanTree(0);
        cleanTree(1);


        FOR(i,1,q) queries[i].process();
    }
}

