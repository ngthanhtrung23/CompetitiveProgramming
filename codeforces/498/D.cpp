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
int a[MN];

struct Node {
    int go[60];
} it[MN * 4];

Node operator + (const Node& a, const Node& b) {
    Node res;
    REP(x,60) {
        res.go[x] = a.go[x] + b.go[(x + a.go[x]) % 60];
    }
    return res;
}

Node init(int a) {
    Node res;
    REP(x,60) {
        res.go[x] = (x % a) ? 1 : 2;
    }
    return res;
}

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

void build(int i, int l, int r) {
    if (l == r) {
        it[i] = init(a[l]);
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
    it[i] = it[CT(i)] + it[CP(i)];
}

void update(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] = init(val);
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, val);
    update(CP(i), mid+1, r, u, val);
    it[i] = it[CT(i)] + it[CP(i)];
}

Node get(int i, int l, int r, int u, int v) {
    if (u <= l && r <= v) return it[i];
    
    int mid = (l + r) >> 1;
    if (v <= mid) return get(CT(i), l, mid, u, v);
    if (mid+1 <= u) return get(CP(i), mid+1, r, u, v);

    Node left = get(CT(i), l, mid, u, v);
    Node right = get(CP(i), mid+1, r, u, v);
    return left + right;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        build(1, 1, n);
        int q; cin >> q;
        while (q--) {
            char typ; cin >> typ;
            if (typ == 'C') {
                int u, val; cin >> u >> val;
                update(1, 1, n, u, val);
            }
            else {
                int u, v; cin >> u >> v;
                --v;
                Node res = get(1, 1, n, u, v);
                cout << res.go[0] << "\n";
            }
        }
    }
    return 0;
}
