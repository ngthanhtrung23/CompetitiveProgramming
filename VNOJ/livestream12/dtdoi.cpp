#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int f[10111];
int s, n, a[111];

int32_t main() {
    ios::sync_with_stdio(0);
    // input
    cin >> n >> s;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int X = *max_element(a+1, a+n+1);

    int res = 0;
    int k = (s - X*X) / X;
    res = k;
    s -= k*X;
    while (s > X*X) {
        ++res;
        s -= X;
    }

    // qhd
    f[0] = 0;
    for (int i = 1; i <= s; i++) {
        f[i] = i;
        for (int j = 1; j <= n; j++) {
            if (a[j] <= i) {
                f[i] = min(f[i], f[i - a[j]] + 1);
            }
        }
    }

    cout << res + f[s] << endl;
    return 0;
}
