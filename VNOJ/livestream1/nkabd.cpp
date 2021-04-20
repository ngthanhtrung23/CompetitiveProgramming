#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int sum[100111];

int32_t main() {
    ios::sync_with_stdio(0);

    // init
    for (int n = 1; n <= 100000; n++) {
        for (int i = 1; i*i <= n; i++) {
            if (n % i == 0) {
                if (i * i == n) {
                    sum[n] += i;
                } else {
                    sum[n] += i + n/i;
                }
            }
        }
    }
    // for (int i = 1; i <= 10; i++) cout << sum[i] << ' '; cout << endl;

    int l, r;
    while (cin >> l >> r) {
        int res = 0;
        for (int i = l; i <= r; i++) {
            if (sum[i] - i > i) {
                res++;
            }
        }
        cout << res << '\n';
    }

    return 0;
}
