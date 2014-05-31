#include <iostream>
#include <cstring>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define F first
#define S second
using namespace std;

const int MN = 411;

struct Aho {
    int qu[MN], suffixLink[MN];
    int leaf[MN];
    int link[MN][22];
    int sz;

    void init() {
        sz = 0;
        memset(suffixLink, 0, sizeof suffixLink);
        leaf[0] = 0;
        memset(link[0], -1, sizeof link[0]);
    }
    int getChild(int type, int v, int c) {
        while (1) {
            if (link[v][c] >= 0) return link[v][c];
            if (type == 1) return 0;
            if (!v) return 0;
            v = suffixLink[v];
        }
    }
    void buildLink() {
        int first, last;
        qu[first = last = 1] = 0;
        while (first <= last) {
            int u = qu[first++];
            REP(c,20) {
                int v = link[u][c];
                if (v < 0) continue;
                qu[++last] = v;
                if (u == 0) suffixLink[v] = 0;
                else suffixLink[v] = getChild(2, suffixLink[u], c);

                leaf[v] += leaf[suffixLink[v]];
            }
        }
    }
} aho;

struct Num {
    int len;
    int x[211];

    void read() {
        cin >> len;
        FOR(i,1,len) cin >> x[i];
    }
} l, r, a[211];

const int MOD = 1000000007;
int n, m, k;
int cost[211];
int f[211][211][511][2], g[211][211][511];

void update(int &x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int get(const Num &bound, int mustLower) {
    memset(f, 0, sizeof f);
    f[0][0][0][0] = 1;
    FOR(i,0,bound.len-1)
    FOR(p,0,aho.sz)
    FOR(s,0,k)
    REP(lower,2)
    if (f[i][p][s][lower]) {
        REP(cur,m)
        if (cur || i)
        if (lower || cur <= bound.x[i+1]) {
            int next = aho.getChild(2, p, cur);
            int lower2 = lower; if (cur < bound.x[i+1]) lower2 = 1;
            int s2 = s + aho.leaf[next];

            if (s2 <= k) {
                update(f[i+1][next][s2][lower2], f[i][p][s][lower]);
            }
        }
    }
    int res = 0;
    FOR(p,0,aho.sz) FOR(s,0,k) {
        update(res, f[bound.len][p][s][1]);
        if (!mustLower) update(res, f[bound.len][p][s][0]);
    }
    // DEBUG(res);

    memset(g, 0, sizeof g);
    g[0][0][0] = 1;
    FOR(i,0,bound.len-1)
    FOR(p,0,aho.sz)
    FOR(s,0,k)
    if (g[i][p][s]) {
        REP(cur,m)
        if (cur || i) {
            int next = aho.getChild(2, p, cur);
            int s2 = s + aho.leaf[next];

            if (s2 <= k) {
                update(g[i+1][next][s2], g[i][p][s]);
            }
        }
    }

    FOR(len,1,bound.len-1) FOR(p,0,aho.sz) FOR(s,0,k) if (g[len][p][s]) {
        update(res, g[len][p][s]);
    }
    // DEBUG(res);
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> k) {
        aho.init();
        l.read();
        r.read();
        FOR(i,1,n) {
            a[i].read();
            cin >> cost[i];

            int p = 0;
            FOR(tmp,1,a[i].len) {
                int x = a[i].x[tmp];
                int t = aho.getChild(1, p, x);
                if (t > 0) p = t;
                else {
                    ++aho.sz;
                    aho.leaf[aho.sz] = 0;
                    memset(aho.link[aho.sz], -1, sizeof aho.link[aho.sz]);

                    aho.link[p][x] = aho.sz;
                    p = aho.sz;
                }
            }
            aho.leaf[p] += cost[i];
        }
        aho.buildLink();

        cout << (get(r, 0) - get(l, 1) + MOD) % MOD << endl;
    }
    return 0;
}
