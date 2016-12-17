
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n, nBlue, nRed;
char color[22];
int r[22], b[22];
int f[TWO(16) + 11][111];
int nB[TWO(16) + 11], nR[TWO(16) + 11];

void update(int& f, int val) {
    f = max(f, val);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);

    while (cin >> n) {
        // read input
        nBlue = nRed = 0;
        REP(i,n) {
            cin >> color[i] >> r[i] >> b[i];
            if (color[i] == 'R') ++nRed;
            else ++nBlue;
        }
        if (nBlue > 8) {
            swap(nBlue, nRed);
            REP(i,n) {
                color[i] = (char) ('R' + 'B' - color[i]);
                swap(r[i], b[i]);
            }
        }

        // sum
        int sumR = 0, sumB = 0;
        REP(i,n) {
            sumR += r[i];
            sumB += b[i];
        }

        // init
        REP(S,TWO(n)) {
            nB[S] = nR[S] = 0;
            REP(i,n) if (CONTAIN(S,i)) {
                if (color[i] == 'R') ++nR[S];
                else ++nB[S];
            }
        }

        // DP
        memset(f, -1, sizeof f);
        f[0][0] = 0;
        REP(S,TWO(n)) FOR(db,0,100) {
            int cur = f[S][db];
            if (cur < 0) continue;

            REP(i,n) if (!CONTAIN(S,i)) {
                // we add the i-th card
                
                int db2 = min(b[i], nB[S]);
                int dr2 = min(r[i], nR[S]);

                assert(db2 <= 100);

                update(f[S | TWO(i)][db + db2], cur + dr2);
            }
        }

        // ans
        int res = 1e9;
        FOR(db,0,100) {
            int dr = f[TWO(n)-1][db];
            if (dr >= 0) {
                int T = max(sumB - db, sumR - dr);
                assert(T < 1e9);
                res = min(res, T);
            }
        }
        res += n;
        cout << res << endl;
    }
}
