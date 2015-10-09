
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;
struct Event {
    ll d;
    int v;
    int t;
    
    void read() {
        cin >> d >> v >> t;
    }
} a[MN];
ll f[MN], c[MN], it[MN * 4];
int n, nc;

void RR() {
    nc = 0;
    FOR(i,1,n) c[++nc] = a[i].d;
    sort(c+1, c+nc+1);
    nc = unique(c+1, c+nc+1) - c - 1;
}

ll get(int i, int l, int r, ll u, ll v) {
    if (v < c[l] || c[r] < u) return 0;
    if (u <= c[l] && c[r] <= v) return it[i];

    int mid = (l + r) >> 1;
    return max(get(i<<1, l, mid, u, v), get(i<<1|1, mid+1, r, u, v));
}

void update(int i, int l, int r, ll u, ll val) {
    if (u < c[l] || c[r] < u) return ;
    if (l == r) {
        it[i] = val;
        return ;
    }
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, val);
    update(i<<1|1, mid+1, r, u, val);

    it[i] = max(it[i<<1], it[i<<1|1]);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) a[i].read();
        RR();
        memset(it, 0, sizeof it);

        ll res = 0;
        FOR(i,1,n) {
            f[i] = get(1, 1, nc, a[i].d - a[i].t, a[i].d) + a[i].v;
            update(1, 1, nc, a[i].d, f[i]);

            res = max(res, f[i]);
        }
//        PR(f, n);
        cout << res << endl;
    }
}
