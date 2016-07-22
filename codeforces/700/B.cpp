#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;

int n, k;
vector<int> ke[MN];
int sz[MN];
int good[MN], f[MN];
int center = 0;

void dfs1(int u, int fu) {
    sz[u] = good[u];

    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs1(v, u);
        sz[u] += sz[v];
    }

    int ln = k - sz[u];
    if (good[u]) ln = max(ln, 1LL);
    for(int v : ke[u]) {
        if (v == fu) continue;
        ln = max(ln, sz[v]);
    }

    if (ln * 2 <= k) {
        center = u;
    }
}

void dfs2(int u, int fu) {
    for(int v : ke[u]) {
        if (v == fu) continue;
        f[v] = f[u] + 1;
        dfs2(v, u);
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(k) == 1) {
        k *= 2;
        FOR(i,1,n) ke[i].clear();
        memset(sz, 0, sizeof sz);
        memset(good, 0, sizeof good);

        FOR(i,1,k) {
            int u; GI(u); good[u] = 1;
        }
        FOR(i,2,n) {
            int u, v; GI(u); GI(v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        center = -1;

        dfs1(1, -1);
        if (center < 0) throw 1;

        f[center] = 0;
        dfs2(center, -1);

        int res = 0;
        FOR(i,1,n) if (good[i]) res += f[i];
        cout << res << endl;
    }
}
