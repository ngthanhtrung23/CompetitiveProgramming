
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 111;
const int MOD = 1e9 + 7;
int n, k;
vector<int> ke[MN];
int f[111][23][23];
int g[111][23][23];

int combineD(int x, int y) {
    if (x == 22) return y;
    if (y == 22) return x;

    return max(x, y);
}

void dfs(int u, int fu) {
    for(int v : ke[u]) {
        if (v == fu) continue;

        dfs(v, u);
    }

    memset(g[0], 0, sizeof g[0]);

    // u: black
    g[0][22][0] = 1;
    // u: white
    g[0][0][22] = 1;

    int cnt = 0;
    for(int v : ke[u]) if (v != fu) {
        cnt++;
        memset(g[cnt], 0, sizeof g[cnt]);

        // combine f[v] and g

        // d == 22 --> no unsatisfied vertices
        // z == 22 --> no black vertices
        FOR(d,0,22) FOR(z,0,22) if (g[cnt-1][d][z]) {
            FOR(vd,0,22) FOR(vz,0,22) if (f[v][vd][vz]) {
                int newz = min(z, vz + 1);
                int newd = 22;
                if (d != 22 && d + vz + 1 > k) newd = combineD(d, newd);
                if (vd != 22 && vd + 1 + z > k) newd = combineD(vd+1, newd);

                if (newd != 22 && newd > k) continue;

                g[cnt][newd][newz] = (g[cnt][newd][newz]
                        + g[cnt-1][d][z] * f[v][vd][vz]) % MOD;
            }
        }
    }
    FOR(d,0,22) FOR(z,0,22) f[u][d][z] = g[cnt][d][z];
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> k) {
        memset(f, 0, sizeof f);
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        dfs(1, 0);
        int res = 0;
        FOR(z,0,22) res = (res + f[1][22][z]) % MOD;
        cout << res << endl;
    }
}
