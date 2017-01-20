
#include <sstream>
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
#include <stack>
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

int n, m, k;
int c[111][111];
pair<int,int> pos[5011];
int f[5011][3][5011];

void update(int& f, int val) {
    f = min(f, val);
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; GI(ntest);
    FOR(test,1,ntest) {
        GI(n); GI(m); GI(k);
        assert(2 <= n && n <= 100);
        assert(1 <= k && k <= 5000);
        assert(1 <= m && m <= 5000);

        const int MAX = 1000111000111LL;
        FOR(i,1,n) FOR(j,1,n) c[i][j] = MAX;
        FOR(i,1,n) c[i][i] = 0;

        while (m--) {
            int u, v, cost; GI(u); GI(v); GI(cost);
            c[u][v] = min(c[u][v], cost);
            c[v][u] = c[u][v];
        }


        FOR(k,1,n)
            FOR(i,1,n) FOR(j,1,n)
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

//        FOR(i,1,n) PR(c[i],n);

        FOR(i,1,k) {
            GI(pos[i].first);
            GI(pos[i].second);
        }

        FOR(i,0,k+1) REP(t,3) FOR(u,1,n) f[i][t][u] = MAX;
        f[1][0][1] = 0;

        // f[i][t][u] = min cost:
        // - i = first not delivered
        // - t = 0/1/2: not pickup i / picked up i / picked up i+1
        // - u = current position
        FOR(i,1,k) REP(t,3) FOR(u,1,n) {
            int cur = f[i][t][u];
            if (cur == MAX) continue;

            if (t == 0) {
                // Pick up i: (i, 0, u) -> (i, 1, v)
                int v = pos[i].first;
                update(f[i][1][v], cur + c[u][v]);
            }
            if (t == 1) {
                // Deliver i: (i, 1, u) --> (i+1, 0, v)
                int v = pos[i].second;
                update(f[i+1][0][v], cur + c[u][v]);

                // Pickup i+1: (i, 1, u) --> (i, 2, v)
                if (i+1 <= k) {
                    int v = pos[i+1].first;
                    update(f[i][2][v], cur + c[u][v]);
                }
            }
            if (t == 2) {
                // Deliver i: (i, 2, u) --> (i+1, 1, v)
                int v = pos[i].second;
                update(f[i+1][1][v], cur + c[u][v]);
            }
        }
        int res = MAX;
        FOR(x,1,n) update(res, f[k+1][0][x]);
        assert(res == f[k+1][0][pos[k].second]);
        if (res == MAX) res = -1;
        cout << "Case #" << test << ": " << res << endl;
        DEBUG(test);
    }
}
