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
using namespace std;

const int MN = 30111;

int MOD, n, q;
struct Node {
    int x[2][2];

    void read() {
        REP(i,2) {
            REP(j,2) cin >> x[i][j];
        }
    }

    void print() {
        REP(i,2) {
            REP(j,2) cout << x[i][j] << ' ';
            cout << '\n';
        }
    }
} it[MN * 4], I;

Node a[MN];

Node operator * (const Node& a, const Node& b) {
    Node res;
    REP(i,2) REP(j,2) {
        res.x[i][j] = 0;
        REP(k,2) res.x[i][j] = (res.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return res;
}

void build(int i, int l, int r) {
    if (l == r) {
        it[i] = a[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);

    it[i] = it[i<<1] * it[i<<1|1];
}

Node get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return I;
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    return get(i<<1, l, mid, u, v) * get(i<<1|1, mid+1, r, u, v);
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);

    I.x[0][0] = I.x[1][1] = 1;
    while (cin >> MOD >> n >> q) {
        FOR(i,1,n) a[i].read();

        build(1, 1, n);

        while (q--) {
            int u, v; cin >> u >> v;
            get(1, 1, n, u, v).print();
            cout << '\n';
        }
    }
}