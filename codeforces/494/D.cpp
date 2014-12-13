#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
const long long MOD = 1000000007;
int n;
vector< pair<int,int> > ke[MN];
long long sz[MN], sum[MN], sumSq[MN], rev[MN], revSq[MN], h[MN];
int fat[20][MN];
long long len[20][MN];

long long add(long long u, long long v) {
    return (u + v) % MOD;
}
long long sub(long long u, long long v) {
    return (u - v%MOD + MOD) % MOD;
}
long long mul(long long u, long long v) {
    return (u * v) % MOD;
}

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(sum, 0, sizeof sum);
    memset(sumSq, 0, sizeof sumSq);
    memset(rev, 0, sizeof rev);
    memset(revSq, 0, sizeof revSq);
    memset(sz, 0, sizeof sz);
    memset(h, 0, sizeof h);
    memset(fat, 0, sizeof fat);
    memset(len, 0, sizeof len);
}

void initLCA() {
    FOR(d,1,18) {
        FOR(u,1,n) {
            fat[d][u] = fat[d-1][fat[d-1][u]];
            len[d][u] = len[d-1][u] + len[d-1][fat[d-1][u]];
        }
    }
}

long long getPath(int u, int v) {
    long long res = 0;
    if (u == v) return res;
    if (h[u] > h[v]) swap(u, v);
    if (h[u] < h[v]) {
        FORD(d,18,0) {
            int x = fat[d][v];
            if (h[x] >= h[u]) {
                res = add(res, len[d][v]);
                v = x;
            }
        }
    }

    if (u == v) return res;

    FORD(d,18,0)
        if (fat[d][v] != fat[d][u]) {
            res = add(res, len[d][u]);
            res = add(res, len[d][v]);
            u = fat[d][u];
            v = fat[d][v];
        }
    res = add(res, len[0][u] + len[0][v]);
    return res;
}
long long lca(int u, int v) {
    if (u == v) return u;
    if (h[u] > h[v]) swap(u, v);
    if (h[u] < h[v]) {
        FORD(d,18,0) {
            int x = fat[d][v];
            if (h[x] >= h[u]) {
                v = x;
            }
        }
    }

    if (u == v) return u;

    FORD(d,18,0)
        if (fat[d][v] != fat[d][u]) {
            u = fat[d][u];
            v = fat[d][v];
        }
    return fat[0][u];
}

void dfs1(int u, int fu) {
    sz[u] = 1;
    for(auto cur : ke[u]) {
        int v = cur.first;
        if (v == fu) continue;

        h[v] = h[u] + 1;
        fat[0][v] = u;
        len[0][v] = cur.second;
        dfs1(v, u);

        sz[u] += sz[v];
        // sum[u] = sigma( sum[v] + sz[v] )
        sum[u] = add(sum[u], sum[v] + mul(sz[v], cur.second));
        
        // sumSq[u] = sigma( sumSq[v] + 2*sum[v] + sz[v])
        sumSq[u] = add(sumSq[u], sumSq[v]);
        sumSq[u] = add(sumSq[u], mul(2*sum[v], cur.second) + mul(sz[v], mul(cur.second, cur.second)));
    }
}

void dfs2(int u, int fu) {
    if (u == 1) rev[u] = revSq[u] = 0;
    else {
        rev[u] = add(rev[fu], sub(sum[fu], sum[u] + mul(sz[u], len[0][u])));
        rev[u] = add(rev[u], mul(n - sz[u], len[0][u]));

        revSq[u] = mul(n - sz[u], mul(len[0][u], len[0][u]));
        revSq[u] = add(revSq[u], mul(2*sub(rev[fu] + sum[fu], sum[u] + mul(sz[u], len[0][u])), len[0][u]));
        revSq[u] = add(revSq[u], sub(revSq[fu] + sumSq[fu], sumSq[u] + mul(2*sum[u], len[0][u]) + mul(sz[u], mul(len[0][u], len[0][u]))));
    }
    for(auto cur : ke[u]) {
        int v = cur.first;
        if (v == fu) continue;
        dfs2(v, u);
    }
}

int d[111][111];
pair<long long, long long> dfs3(int start, int u, int fu) {
    pair<long long, long long> res = make_pair(d[start][u], mul(d[start][u], d[start][u]));
    for(auto cur : ke[u]) {
        int v = cur.first;
        if (v == fu) continue;
        pair<long long, long long> t = dfs3(start, v, u);
        res.first = add(res.first, t.first);
        res.second = add(res.second, t.second);
    }
    return res;
}
pair<long long, long long> dfs4(int start, int u, int fu) {
    pair<long long, long long> res = make_pair(d[start][u], mul(d[start][u], d[start][u]));
    for(auto cur : ke[u]) {
        int v = cur.first;
        if (v == fu) continue;
        pair<long long, long long> t = dfs4(start, v, u);
        res.first = add(res.first, t.first);
        res.second = add(res.second, t.second);
    }
    return res;
}
void check() {
    FOR(i,1,n) FOR(j,1,n) d[i][j] = MOD;
    FOR(i,1,n) d[i][i] = 0;
    FOR(u,1,n)
        for(auto cur : ke[u]) {
            int v = cur.first;
            d[u][v] = cur.second;
        }

    FOR(k,1,n)
        FOR(i,1,n) FOR(j,1,n)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    FOR(i,1,n) {
        pair<long long, long long> cur = dfs3(i, i, fat[0][i]);
        assert(cur.first == sum[i]);
        assert(cur.second == sumSq[i]);

        if (i > 1) {
            cur = dfs4(i, fat[0][i], i);
            assert(cur.first == rev[i]);
            assert(cur.second == revSq[i]);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        init();
        FOR(i,2,n) {
            int c, u, v; cin >> u >> v >> c;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        h[1] = 1;
        dfs1(1, -1);
        dfs2(1, -1);

//        check();
        initLCA();

        int q; cin >> q;
        while (q--) {
            int u, v; cin >> u >> v;
            long long l = getPath(u, v);
            int g = lca(u, v);
            if (g == v) {
                long long res = sumSq[u];
                res = sub(res, 2*(mul(mul(l,l),n-sz[v]) + mul(2*l, rev[v]) + revSq[v]));
                res = add(res, revSq[u]);

                cout << res << "\n";
                continue;
            }
            // sum1 = sz[v]*len*len + sumSq[v] + 2*len*sum[v]
            long long sum1 = add(mul(sz[v], mul(l,l)), sumSq[v] + mul(2*l, sum[v]));
            long long res = sub(2*sum1, add(revSq[u], sumSq[u]));
            cout << res << "\n";
        }
    }
    return 0;
}
