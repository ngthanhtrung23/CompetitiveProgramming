
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 111;

int c[MN][MN]; // c[i][j] = shortest path from i -> j
int a[10111];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    // input
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c[i][j];
        }
    }

    // floyd
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
            }
        }
    }

    // 
    int res = 0;
    a[0] = 1;
    for (int i = 1; i <= m; i++) {
        res += c[a[i-1]][a[i]];
    }
    cout << res << endl;

    return 0;
}
