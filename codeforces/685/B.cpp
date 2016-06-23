#include <bits/stdc++.h>
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

const int MN = 300111;

int n, q, f[MN], cen[MN], father[MN], ln[MN], save[MN];
vector<int> ke[MN];

bool isCentroid(int u, int x) {
    if (x == u) return true;

    // cut at x, what is max size?
    int res = f[u] - f[x];
    res = max(res, ln[x]);
    return res * 2 <= f[u];
}

void dfs1(int u) {
    f[u] = 1;
    ln[u] = 0;
    save[u] = -1;
    for(int v : ke[u]) {
        dfs1(v);
        f[u] += f[v];

        if (f[v] > ln[u]) {
            ln[u] = f[v];
            save[u] = v;
        }
    }

    if (ln[u] == 0) cen[u] = u;
    else {
        int x = cen[save[u]];
        while (!isCentroid(u, x)) {
            x = father[x];
        }
        cen[u] = x;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int fi; scanf("%d", &fi);
            father[i] = fi;
            ke[fi].push_back(i);
        }
        dfs1(1);
        while (q--) {
            int u; scanf("%d", &u);
            printf("%d\n", cen[u]);
        }
    }
}
