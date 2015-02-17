
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
int n, a[MN];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

struct Node {
    long long cnt[22];
    int xored;
    long long sum;
} it[MN * 8];

void refine(int i) {
    it[i].sum = 0;
    REP(t,20) {
        it[i].sum += it[i].cnt[t] << (long long) t;
    }
}

void up(int i) {
    REP(t,20)
        it[i].cnt[t] = it[CT(i)].cnt[t] + it[CP(i)].cnt[t];
    refine(i);
}

void cover(int i, int sz, int val) {
    it[i].xored ^= val;
    REP(t,20) if (CONTAIN(val, t)) {
        it[i].cnt[t] = sz - it[i].cnt[t];
    }
    refine(i);
}

void down(int i, int l, int r, int mid) {
    if (it[i].xored) {
        cover(CT(i), mid - l + 1, it[i].xored);
        cover(CP(i), r - mid, it[i].xored);
        it[i].xored = 0;
    }
}

void build(int i, int l, int r) {
    it[i].xored = 0;
    if (l == r) {
        it[i].sum = a[l];
        REP(t,20) {
            if (CONTAIN(a[l], t)) it[i].cnt[t] = 1;
            else it[i].cnt[t] = 0;
        }
        refine(i);
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
    up(i);
}

long long get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum;

    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    long long res = get(CT(i), l, mid, u, v) + get(CP(i), mid+1, r, u, v);
    return res;
}

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        cover(i, r - l + 1, val);
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    update(CT(i), l, mid, u, v, val);
    update(CP(i), mid+1, r, u, v, val);

    up(i);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        build(1, 1, n);
        int q; cin >> q;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u, v; cin >> u >> v;
                cout << get(1, 1, n, u, v) << '\n';
            }
            else {
                int u, v, val; cin >> u >> v >> val;
                update(1, 1, n, u, v, val);
            }
        }
    }
    return 0;
}

