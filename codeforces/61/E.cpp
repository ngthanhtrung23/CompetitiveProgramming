
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

const int MN = 1000111;
int a[MN], f[MN], c[MN], n;
long long bit[MN], g[MN];

void RR() {
    FOR(i,1,n) c[i] = a[i];
    sort(c+1, c+n+1);
    FOR(i,1,n) a[i] = lower_bound(c+1, c+n+1, a[i]) - c;
}

#define _(X) ((X) & (-(X)))

void update(int u, int val) {
    while (u <= n) {
        bit[u] += val;
        u += _(u);
    }
}

long long get(int u) {
    long long res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        RR();
        memset(bit, 0, sizeof bit);
        FORD(i,n,1) {
            f[i] = get(a[i] - 1);
            update(a[i], 1);
        }

        memset(bit, 0, sizeof bit);
        FORD(i,n,1) {
            g[i] = get(a[i] - 1);
            update(a[i], f[i]);
        }
//        PR(a, n);
//        PR(f, n);
//        PR(g, n);
        long long res = 0;
        FOR(i,1,n) res += g[i];
        cout << res << endl;
    }
    return 0;
}

