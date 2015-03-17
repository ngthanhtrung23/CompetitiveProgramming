
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

const int MN = 400111;
int n;

struct Point {
    int x, w, sum, diff;
} x[MN];

int bit[MN];

#define _(X) ((X) & (-(X)))

int get(int u) {
    int res = 0;
    while (u > 0) {
        res = max(res, bit[u]);
        u -= _(u);
    }
    return res;
}

void update(int u, int val) {
    while (u < MN) {
        bit[u] = max(bit[u], val);
        u += _(u);
    }
}

int c[MN], f[MN];

bool operator < (const Point& a, const Point& b) {
    return a.x < b.x;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d%d", &x[i].x, &x[i].w);
            x[i].sum = x[i].x + x[i].w;
            x[i].diff = x[i].x - x[i].w;
        }
        sort(x+1, x+n+1);

        int sc = 0;
        FOR(i,1,n) {
            c[++sc] = x[i].sum;
            c[++sc] = x[i].diff;
        }
        sort(c+1, c+sc+1);
        sc = unique(c+1, c+sc+1) - c - 1;
        FOR(i,1,n) {
            x[i].sum = lower_bound(c+1, c+sc+1, x[i].sum) - c;
            x[i].diff = lower_bound(c+1, c+sc+1, x[i].diff) - c;
        }

        int res = 0;
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            f[i] = get(x[i].diff) + 1;
            update(x[i].sum, f[i]);

            res = max(res, f[i]);
        }
        cout << res << endl;
    }
    return 0;
}
