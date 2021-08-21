#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MN = 311;
int d[MN][MN][MN];

int nRow, nCol, k;
string board[MN];
string need;

bool inside(int u, int v) {
    return 1 <= u && u <= nRow
        && 1 <= v && v <= nCol;
}

const int dirs[5] = {0, 1, 0, -1, 0};

int32_t main() {
    ios::sync_with_stdio(0);
    // input
    cin >> nRow >> nCol >> k;
    cin >> need; need = " " + need + " ";
    FOR(i,1,nRow) {
        cin >> board[i];
        board[i] = " " + board[i] + " ";
    }

    // bfs
    // start: (0, i, j)
    queue<tuple<int,int,int> > qu;
    memset(d, -1, sizeof d);

    FOR(i,1,nRow) FOR(j,1,nCol) {
        qu.push({0, i, j});
        d[0][i][j] = 0;
    }

    while (!qu.empty()) {
        auto [matched, u, v] = qu.front(); qu.pop();
        if (matched == k) {
            cout << d[matched][u][v] << endl;
            return 0;
        }

        for (int dir = 0; dir < 4; dir++) {
            int uu = u + dirs[dir];
            int vv = v + dirs[dir + 1];
            
            if (!inside(uu, vv)) continue;

            int matched2 = matched;
            if (need[matched2+1] == board[uu][vv]) ++matched2;

            if (d[matched2][uu][vv] < 0) {
                d[matched2][uu][vv] = d[matched][u][v] + 1;
                qu.push({matched2, uu, vv});
            }
        }
    }
    assert(false);

    return 0;
}
