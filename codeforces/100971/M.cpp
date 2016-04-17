#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())

#define TWO(X) (1<<(X))
using namespace std;

const int MN = 200111;
const int INF = 1e9;
int a[MN], n, k, f[MN];

struct Node {
    int mask, nn;
} it[MN * 4];

void build(int i, int l, int r) {
    if (l == r) {
        it[i].nn = INF;
        it[i].mask = TWO(a[l]);
        return ;
    }
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);

    it[i].nn = INF;
    it[i].mask = it[i<<1].mask | it[i<<1|1].mask;
}

int getMask(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].mask;

    int mid = (l + r) >> 1;
    return getMask(i<<1, l, mid, u, v) | getMask(i<<1|1, mid+1, r, u, v);
}
int getMin(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return INF;
    if (u <= l && r <= v) return it[i].nn;

    int mid = (l + r) >> 1;
    return min(getMin(i<<1, l, mid, u, v), getMin(i<<1|1, mid+1, r, u, v));
}
void update(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].nn = val;
        return ;
    }
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, val);
    update(i<<1|1, mid+1, r, u, val);

    it[i].nn = min(it[i<<1].nn, it[i<<1|1].nn);
}

int count(int l, int r) {
    if (l > r) return 0;
    return __builtin_popcount(getMask(1, 1, n, l, r));
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> k) {
        string s; cin >> s;
        n = SZ(s);
        FOR(i,1,n) {
            a[i] = s[i-1] - 'a';
        }
        build(1, 1, n);

        FOR(i,1,n) f[i] = INF;

        int l = 1, r = 1;
        FOR(i,1,n) {
            if (count(1, i) < k) {
                f[i] = INF;
                continue;
            }

            while (count(l, i) > k) ++l;
            while (count(r+1, i) >= k) ++r;

            if (l == 1) f[i] = 1;
            else {
                f[i] = getMin(1, 1, n, l-1, r-1) + 1;
            }
            update(1, 1, n, i, f[i]);
        }

        FOR(i,1,n) if (f[i] >= INF) f[i] = -1;
        FOR(i,1,n) printf("%d ", f[i]); puts("");
    }
}
