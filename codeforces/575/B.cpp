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

const int MN = 100111;
const int MOD = 1e9 + 7;
const int MN2 = 1000111;

vector< pair<int,int> > ke[MN];
int n, father[20][MN], up[20][MN], down[20][MN], h[MN], p2[MN2], dirTo[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(up, 0, sizeof up);
    memset(down, 0, sizeof down);
}

void dfs(int u, int fu) {
    for(auto e : ke[u]) {
        int v = e.first;
        if (v == fu) continue;

        father[0][v] = u;
        h[v] = h[u] + 1;
        dirTo[v] = e.second;

        dfs(v, u);
    }
}

void initLCA() {
    FOR(t,1,19) {
        FOR(u,1,n)
            father[t][u] = father[t-1][ father[t-1][u] ];
    }
}

void go(int u, int v) {
    // u --> l --> v
    if (h[u] > h[v]) {
        FORD(i,19,0) {
            int x = father[i][u];
            if (h[x] >= h[v]) {
                up[i][u]++;
                u = x;
            }
        }
    }
    if (h[v] > h[u]) {
        FORD(i,19,0) {
            int x = father[i][v];
            if (h[x] >= h[u]) {
                down[i][v]++;
                v = x;
            }
        }
    }
    if (u == v) return ;
    // h[u] = h[v]
    FORD(i,19,0)
        if (father[i][u] != father[i][v]) {
            up[i][u]++;
            down[i][v]++;

            u = father[i][u];
            v = father[i][v];
        }

    up[0][u]++;
    down[0][v]++;
}

void solve() {
    FORD(i,19,1) {
        FOR(u,1,n) {
            int x = father[i-1][u];
            if (up[i][u]) {
                up[i-1][u] += up[i][u];
                up[i-1][x] += up[i][u];
            }
            if (down[i][u]) {
                down[i-1][u] += down[i][u];
                down[i-1][x] += down[i][u];
            }
        }
    }
    ll res = 0;

    FOR(i,2,n) {
        int t = 0;
        if (dirTo[i] == 1) {
            t = up[0][i];
        }
        else if (dirTo[i] == -1) {
            t = down[0][i];
        }

//        if (t)
            res = (res + p2[t] - 1 + MOD) % MOD;
    }
    cout << res << endl;
}

int main() {
    p2[0] = 1; FOR(i,1,MN2 - 1) p2[i] = p2[i-1] * 2 % MOD;
    while (scanf("%d", &n) == 1) {
        init();
        FOR(i,2,n) {
            int u, v, x; scanf("%d%d%d", &u, &v, &x);
            ke[u].push_back(make_pair(v, x));
            ke[v].push_back(make_pair(u, -x));
        }
        h[1] = 1;
        dfs(1, -1);
        initLCA();
        int k; scanf("%d", &k);
        int cur = 1;
        FOR(i,1,k) {
            int u; scanf("%d", &u);
            go(cur, u);

            cur = u;
        }
        solve();
    }
}