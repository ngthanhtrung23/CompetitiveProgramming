#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

#define TWO(X) (1<<(X))
#define CONTAIN(S,i) (((S) >> (i)) & 1)

const int MN = 7;
int n;
int need[MN + 2][MN + 2];

// f[row][mask] = how many ways to paint up to this row.
//                mask = bitmask representing last row.
int f[MN + 1][TWO(MN * 2)];

// Check if this mask can be 1st or last row:
// - Every pair of (even, odd) bits must be equal.
bool goodForFirstAndLastRow(int mask) {
    for (int i = 0; i < 2*n; i += 2) {
        if (CONTAIN(mask, i) != CONTAIN(mask, i+1)) {
            return false;
        }
    }
    return true;
}

// Given a mask of last row, mod2 = row % 2.
// Return bitmask of vertical edges.
int getVers(int mask, int mod2) {
    int res = 0;
    REP(col,n+1-mod2) {
        int prev = col * 2 - 1 + mod2;
        int next = col * 2 + mod2;

        int cur = 0;
        if (prev >= 0) cur ^= CONTAIN(mask, prev);
        if (next < 2*n) cur ^= CONTAIN(mask, next);

        res += cur * TWO(col);
    }
    return res;
}

vector<int> verToMasks[2][TWO(MN + 1)];
int maskToVer[2][TWO(MN * 2)];

bool match(int val, int need) {
    return need < 0 || val == need;
}

bool check(int row, int mask, int ver, int nextMask) {
    if (row % 2 == 0) {
        REP(col,n) {
            int has = 0;
            // 2 top edges
            has += CONTAIN(mask, 2*col);
            has += CONTAIN(mask, 2*col + 1);

            // 2 vertical edges
            has += CONTAIN(ver, col);
            has += CONTAIN(ver, col + 1);

            // 2 bottom edges
            has += CONTAIN(nextMask, 2*col);
            has += CONTAIN(nextMask, 2*col + 1);

            if (!match(has, need[row][col])) return false;
        }
    } else {
        REP(col, n-1) {
            int has = 0;
            // 2 top edges
            has += CONTAIN(mask, 2*col + 1);
            has += CONTAIN(mask, 2*col + 2);

            // 2 vertical edges
            has += CONTAIN(ver, col);
            has += CONTAIN(ver, col + 1);

            // 2 bottom edges
            has += CONTAIN(nextMask, 2*col + 1);
            has += CONTAIN(nextMask, 2*col + 2);

            if (!match(has, need[row][col])) return false;
        }
    }
    return true;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin >> n;
    REP(i,n) {
        int nCols = (i % 2 == 0) ? n : n-1;
        REP(j,nCols) cin >> need[i][j];
    }

    REP(mask,TWO(2*n)) {
        if (goodForFirstAndLastRow(mask)) {
            f[0][mask]++;
        }

        REP(mod2,2) {
            int ver = getVers(mask, mod2);
            verToMasks[mod2][ver].push_back(mask);
            maskToVer[mod2][mask] = ver;
        }
    }

    REP(row,n) {
        REP(mask,TWO(2*n)) {
            int cur = f[row][mask];
            if (!cur) continue;

            int ver = maskToVer[row % 2][mask];

            // current & next row must have same vertical edges.
            for (int nextMask : verToMasks[row % 2][ver]) {
                if (check(row, mask, ver, nextMask)) {
                    f[row + 1][nextMask] += cur;
                    assert(f[row + 1][nextMask] >= 0);
                }
            }
        }
    }

    int res = 0;
    REP(mask,TWO(2*n)) {
        if (goodForFirstAndLastRow(mask)) {
            res += f[n][mask];
            assert(res >= 0);
        }
    }
    cout << res << endl;
    return 0;
}

