#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

struct Node {
    int ln;
    long long sum;
} it[MN * 3];

int n, q, a[MN];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

inline int better(int x, int y) {
    return (a[x] > a[y]) ? x : y;
}

void update(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].ln = l;
        it[i].sum = val;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, val);
    update(CP(i), mid+1, r, u, val);

    it[i].sum = it[CT(i)].sum + it[CP(i)].sum;
    it[i].ln = better(it[CT(i)].ln, it[CP(i)].ln);
}

long long getSum(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum;

    int mid = (l + r) >> 1;
    return getSum(CT(i), l, mid, u, v) + getSum(CP(i), mid+1, r, u, v);
}

int getMax(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].ln;
    int mid = (l + r) >> 1;

    return better(getMax(CT(i), l, mid, u, v), getMax(CP(i), mid+1, r, u, v));
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> q) {
        FOR(i,1,n) cin >> a[i];
        memset(it, 0, sizeof it);

        FOR(i,1,n) update(1,1,n,i,a[i]);

        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u, v; cin >> u >> v;
                cout << getSum(1, 1, n, u, v) << endl;
            }
            else if (typ == 2) {
                int u, v, x; cin >> u >> v >> x;
                while (true) {
                    int i = getMax(1, 1, n, u, v);
                    if (a[i] < x) break;

                    a[i] = a[i] % x;
                    update(1, 1, n, i, a[i]);
                }
            }
            else {
                int u, val; cin >> u >> val;
                a[u] = val;
                update(1, 1, n, u, val);
            }
        }
    }
    return 0;
}
