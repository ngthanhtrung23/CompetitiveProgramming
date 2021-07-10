#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 100111;
const int MOD = 2111992;

int f[MN], s[MN], n, k;

int32_t main() {
    ios::sync_with_stdio(0);
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int j = max(i - (k+1), 0LL);
        f[i] = (1 + s[j]) % MOD;

        s[i] = (s[i-1] + f[i]) % MOD;
    }
    cout << (s[n] + 1) % MOD << endl;

    return 0;
}
