#include "bits/stdc++.h"

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

int f[11][111][111][111];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    FOR(u,1,10) {
        FOR(x,1,100) FOR(y,1,100) FOR(z,1,100) {
            int& cur = f[u][x][y][z];
            cur = max({
                    f[u][x-1][y][z],
                    f[u][x][y-1][z],
                    f[u][x][y][z-1],
            });

            // do not cut
            if (x <= y && x <= z && x >= u) {
                cur = max(cur, y*z);
            }
            if (y <= x && y <= z && y >= u) {
                cur = max(cur, x*z);
            }
            if (z <= x && z <= y && z >= u) {
                cur = max(cur, x*y);
            }

            // optimal cut is always at coordinate u
            if (x > u) {
                cur = max(cur, f[u][u][y][z] + f[u][x-u][y][z]);
            }
            if (y > u) {
                cur = max(cur, f[u][x][u][z] + f[u][x][y-u][z]);
            }
            if (z > u) {
                cur = max(cur, f[u][x][y][u] + f[u][x][y][z - u]);
            }
        }
    }

    int ntest; cin >> ntest;
    while (ntest--) {
        int x, y, z, u; cin >> x >> y >> z >> u;
        cout << f[u][x][y][z] << '\n';
    }

    return 0;
}
