#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 1011;
int a[MN][MN];

int32_t main() {
    ios::sync_with_stdio(0);
    int n, k;
    while (cin >> n >> k) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];

                a[i][j] = a[i-1][j]
                    + a[i][j-1]
                    - a[i-1][j-1]
                    + a[i][j];
            }
        }

        int res = 0;
        for (int i = k; i <= n; i++) {
            for (int j = k; j <= n; j++) {
                res = max(res,
                        a[i][j]
                        - a[i-k][j]
                        - a[i][j-k]
                        + a[i-k][j-k]);
            }
        }
        cout << res << endl;
    }
    return 0;
}
