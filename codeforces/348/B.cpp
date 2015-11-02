
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

int n;
ll a[MN], nChild[MN], f[MN], res;
vector<int> ke[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
}

ll lcm(ll a, ll b) {
    return a / __gcd(a, b) * b;
}

void dfs1(int u, int fu) {
    nChild[u] = 0;

    f[u] = 1;
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;

        ++nChild[u];
        dfs1(v, u);

        f[u] = lcm(f[u], f[v]);
        if (f[u] < 0) throw 1;
    }
    if (nChild[u] == 0) f[u] = 1;
    else {
        f[u] *= nChild[u];
    }
}

void dfs2(int u, int fu, ll need) {
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs2(v, u, need / nChild[u]);
    }

    if (nChild[u] == 0) {
        res = min(res, a[u] / need);
    }
}

ll dfs3(int u, int fu, ll need) {
    ll res = 0;
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;

        res += dfs3(v, u, need / nChild[u]);
    }
    if (nChild[u] == 0) res += a[u] - need;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        init();
        ll sum = 0;
        FOR(i,1,n) {
            int x; scanf("%d", &x);
            a[i] = x;
            sum += x;
        }
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        try {
            dfs1(1, -1);
            res = 1000111000111000111LL;
            dfs2(1, -1, f[1]);

            cout << dfs3(1, -1, res * f[1]) << endl;
        }
        catch (int e) {
            cout << sum << endl;
        }
    }
}
