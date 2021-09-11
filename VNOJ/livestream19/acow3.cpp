//  C 
// CGC
//  C 

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int di[4] = {-1, 0, 0, 1};
const int dj[4] = {0, -1, 1, 0};

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int nRow, nCol; cin >> nRow >> nCol;

    auto inside = [&] (int i, int j) {
        return i >= 0 && i < nRow
            && j >= 0 && j < nCol;
    };

    vector<string> board(nRow);
    for (auto& row : board) cin >> row;

    set< pair< pair<int,int>, pair<int,int> > > matched;

    auto check = [&] (int i, int j) {
        for (int dir1 = 0; dir1 < 4; dir1++) {
            int r1 = i + di[dir1];
            int c1 = j + dj[dir1];
            if (!inside(r1, c1)
                    || board[r1][c1] != 'C') {
                continue;
            }

            for (int dir2 = dir1 + 1; dir2 < 4; dir2++) {
                int r2 = i + di[dir2];
                int c2 = j + dj[dir2];
                if (!inside(r2, c2)
                        || board[r2][c2] != 'C') {
                    continue;
                }

                if (matched.count({{r1, c1}, {r2, c2}})) {
                    continue;
                }

                matched.insert({{r1, c1}, {r2, c2}});
                return;
            }
        }
    };

    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            if (board[i][j] == 'G') {
                check(i, j);
            }
        }
    }

    cout << SZ(matched) << endl;

    return 0;
}
