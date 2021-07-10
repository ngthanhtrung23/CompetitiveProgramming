#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 1011;
int a[MN][MN], f[MN][MN];

int32_t main() {
    ios::sync_with_stdio(0);
    // input
    int nRow, nCol; cin >> nRow >> nCol;
    for (int i = 1; i <= nRow; i++) {
        for (int j = 1; j <= nCol; j++) {
            cin >> a[i][j];
        }
    }

    // qhd
    int res = 0;
    for (int color = 1; color >= 0; color--) {
        for (int i = 1; i <= nRow; i++) {
            for (int j = 1; j <= nCol; j++) {
                if (a[i][j] != color) {
                    f[i][j] = 0;
                    continue;
                } else {
                    f[i][j] = min({f[i-1][j], f[i][j-1], f[i-1][j-1]}) + 1;
                }
            }
        }

        for (int i = 1; i <= nRow; i++) {
            res = max(res, *max_element(f[i]+1, f[i]+nCol+1));
        }
    }
    cout << res << endl;
    return 0;
}
