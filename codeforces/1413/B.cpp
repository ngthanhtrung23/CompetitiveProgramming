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

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int nRow, nCol;
        cin >> nRow >> nCol;
        vector< vector<int> > rows(nRow), cols(nCol);
        vector<int> valueToRowId(nRow * nCol + 1);

        for (auto& row : rows) {
            row.resize(nCol);
            for (auto& val : row) cin >> val;
        }

        for (auto& col : cols) {
            col.resize(nRow);
            REP(i,nRow) {
                cin >> col[i];
                valueToRowId[col[i]] = i;
            }
        }

        vector<vector<int>> board(nRow);
        for (auto& row : rows) {
            int val = row[0];
            board[valueToRowId[val]] = row;
        }

        for (auto& row : board) {
            for (auto& val : row) cout << val << ' ';
            cout << '\n';
        }
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
