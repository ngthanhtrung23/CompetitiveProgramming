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

const int MN = 311;
int m, n, a[MN][MN], row[MN][MN], f[2][MN][MN];

void update(int& x, int val) {
    x = max(x, val);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("livada2.in", "r", stdin);
    freopen("livada2.out", "w", stdout);
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        scanf("%d%d", &m, &n);
        int res = -1000111000;
        FOR(i,1,m) FOR(j,1,n) {
            scanf("%d", &a[i][j]);
            row[i][j] = row[i][j-1] + a[i][j];

            update(res, a[i][j]);
        }

        FOR(i,0,n) FOR(j,0,n) f[0][i][j] = -1000111000;

        FOR(i,1,m) {
            int t = i % 2;

            FOR(j1,1,n) FOR(j2,j1,n) {
                int cur = row[i][j2] - row[i][j1-1];

                f[t][j1][j2] = cur;
                update(f[t][j1][j2], f[1-t][j1][j2] + cur);

                update(res, f[t][j1][j2]);
            }

            // co
            FORD(diff,n-2,0) {
                FOR(j1,1,n) {
                    int j2 = j1 + diff;
                    if (j2 > n) break;

                    if (j1 > 1) update(f[t][j1][j2], f[t][j1-1][j2]);
                    if (j2 < n) update(f[t][j1][j2], f[t][j1][j2+1]);
                }
            }
            // mo
            FOR(diff,1,n-1) {
                FOR(j1,1,n) {
                    int j2 = j1 + diff;
                    if (j2 > n) break;

                    update(f[t][j1][j2], max(f[t][j1+1][j2], f[t][j1][j2-1]));
                }
            }
        }

        cout << res << endl;
    }
}
