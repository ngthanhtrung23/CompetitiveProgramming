#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MAX_ROW = 2311;
const int MAX_COL = 12;

int nRow, nCol;
int hor[MAX_ROW][MAX_COL];
int ver[MAX_ROW][MAX_COL];
int d[MAX_ROW][MAX_COL];

bool inside(int i, int j) {
    return 0 <= i && i <= nRow
        && 1 <= j && j <= nCol;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    cin >> nRow >> nCol;
    for (int i = 1; i <= nRow; i++) {
        for (int j = 1; j <= nCol; j++) {
            cin >> hor[i][j];
        }
        for (int j = 1; j <= nCol-1; j++) {
            cin >> ver[i][j];
        }
    }

    // dijkstra
    memset(d, 0x3f, sizeof d);
    set< tuple<int, int, int> > all;
    for (int j = 1; j <= nCol; j++) {
        d[0][j] = 0;
        all.insert({0, 0, j});
    }

    auto update = [&] (int r, int c, int cost) {
        if (!inside(r, c)) return;

        if (cost < d[r][c]) {
            d[r][c] = cost;
            all.insert({cost, r, c});
        }
    };

    while (!all.empty()) {
        auto [len, r, c] = *all.begin();
        all.erase(all.begin());

        if (len != d[r][c]) continue;

        update(r+1, c, len + hor[r+1][c]);
        update(r-1, c, len + hor[r][c]);

        update(r, c+1, len + ver[r][c]);
        update(r, c-1, len + ver[r][c-1]);
    }

    cout << d[nRow][nCol] << endl;
    return 0;
}
