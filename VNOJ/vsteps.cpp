#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MOD = 14062008;

bool bad[100111];
int f[100111];

int32_t main() {
    ios::sync_with_stdio(0);
    int n, k;
    while (cin >> n >> k) {
        memset(bad, false, sizeof bad);
        memset(f, 0, sizeof f);

        while (k--) {
            int u; cin >> u;
            bad[u] = true;
        }

        f[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (bad[i]) continue;

            f[i] = (f[i-1] + f[i-2]) % MOD;
        }
        cout << f[n] << endl;
    }
    return 0;
}
