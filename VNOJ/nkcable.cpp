#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 25011;
int a[MN], f[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n) {
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }

        for (int i = 2; i <= n; i++) {
            cin >> a[i];
        }

        // f[i] = min cost connect 1..i
        f[2] = a[2];
        for (int i = 3; i <= n; i++) {
            if (i == 3) {
                f[i] = f[i-1] + a[i];
            } else {
                f[i] = min(
                        f[i-1] + a[i],
                        f[i-2] + a[i]);
            }
        }
        cout << f[n] << endl;
    }
    return 0;
}
/*

1-2: 2
2-3: 2
3-4: 3
4-5: 2
5-6: 2

 */
