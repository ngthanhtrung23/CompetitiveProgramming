
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define left left__
#define right right__
using namespace std;

const long long MOD = 1e9 + 7;

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x*x % MOD, k >> 1);
    if (k & 1) return mid * x % MOD;
    else return mid;
}

long long inverse(long long x) {
    return power(x, MOD - 2);
}

const int MN = 200111;

long long f[2][MN], g[2][MN];
long long left[2][MN], right[2][MN];
vector<int> ke[MN];
int n;

void dfs1(int u) {
    f[0][u] = 1LL;
    f[1][u] = 1LL;

    for(int v : ke[u]) {
        dfs1(v);
        f[0][u] = (f[0][u] * f[0][v]) % MOD;
        f[1][u] = (f[1][u] * (f[1][v] + 2*f[0][v])) % MOD;
    }

    long long p[2];
    p[0] = p[1] = 1LL;
    for(int v : ke[u]) {
        left[0][v] = p[0];
        left[1][v] = p[1];

        p[0] = p[0] * f[0][v] % MOD;
        p[1] = p[1] * (f[1][v] + f[0][v] + f[0][v]) % MOD;
    }
    p[0] = p[1] = 1LL;
    FORD(id,ke[u].size()-1,0) {
        int v = ke[u][id];

        right[0][v] = p[0];
        right[1][v] = p[1];

        p[0] = p[0] * f[0][v] % MOD;
        p[1] = p[1] * (f[1][v] + f[0][v] + f[0][v]) % MOD;
    }

    f[1][u] = (f[1][u] - f[0][u] + MOD) % MOD;
}

void dfs2(int u, int fu) {
    if (u == 1) {
        g[0][u] = 1LL;
        g[1][u] = 0LL;
    }
    else {
        long long f_0_ignore = left[0][u] * right[0][u] % MOD;
        g[0][u] = g[0][fu] * f_0_ignore % MOD;


        long long p = left[1][u] * right[1][u] % MOD;

        g[1][u] = (g[1][fu] + g[0][fu]) * p % MOD;
    }

    for(int v : ke[u]) {
        dfs2(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int fi; scanf("%d", &fi);
            ke[fi].push_back(i);
        }
        dfs1(1);
        dfs2(1, -1);

//        PR(f[0], n);
//        PR(f[1], n);
//        PR(g[0], n);
//        PR(g[1], n);

        FOR(u,1,n) {
            long long res = (f[0][u] + f[1][u]) * (g[0][u] + g[1][u]) % MOD;
            printf("%d ", (int) res);
        }
        puts("");
    }
    return 0;
}
