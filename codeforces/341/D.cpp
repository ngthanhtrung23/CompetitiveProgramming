
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

#define ll long long
#define _(X) ((X) & (-(X)))

const int MN = 1011;
ll bit[4][MN][MN];

int n, q;

ll get(int t, int u, int v) {
    ll res = 0;
    for(int i = u; i > 0; i -= _(i))
        for(int j = v; j > 0; j -= _(j)) {
            res ^= bit[t][i][j];
        }
    return res;
}

void update(int t, int u, int v, ll val) {
    for(int i = u; i < MN; i += _(i))
        for(int j = v; j < MN; j += _(j))
            bit[t][i][j] ^= val;
}

ll get2(int u, int v) {
    ll res = 0;
    res ^= get(0, u, v);

    if (v & 1) res ^= get(1, u, n) ^ get(1, u, v);
    if (u & 1) res ^= get(2, n, v) ^ get(2, u, v);

    if ((u & 1) && (v & 1)) {
        res ^= get(3, n, n) ^ get(3, u, n) ^ get(3, n, v) ^ get(3, u, v);
    }
    return res;
}

void update2(int u, int v, ll val) {
    if (u <= 0 || v <= 0) return ;

    if ((u & 1) && (v & 1))
        update(0, u, v, val);

    if (u & 1) update(1, u, v, val);
    if (v & 1) update(2, u, v, val);
    update(3, u, v, val);
}

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        memset(bit, 0, sizeof bit);
        while (q--) {
            int typ; scanf("%d", &typ);
            int x0, y0, x1, y1;
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            if (typ == 1) {
                printf("%I64d\n", 
                        ( get2(x1, y1)
                        ^ get2(x0-1, y1)
                        ^ get2(x1, y0-1)
                        ^ get2(x0-1, y0-1)));
            }
            else {
                ll val; scanf("%I64d", &val);
                update2(x1, y1, val);
                update2(x0-1, y1, val);
                update2(x1, y0-1, val);
                update2(x0-1, y0-1, val);
            }
        }
    }
    return 0;
}
