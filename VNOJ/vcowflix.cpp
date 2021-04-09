
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    int limit, n;
    while (cin >> limit >> n) {
        vector<int> a(n);
        for (int& x : a) cin >> x;

        int res = 0;
        for (int mask = 0; mask < (1<<n); mask++) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                if ((mask >> i) & 1) {
                    sum += a[i];
                }
            }
            if (sum <= limit) res = max(res, sum);
        }
        cout << res << '\n';
    }
    return 0;
}
