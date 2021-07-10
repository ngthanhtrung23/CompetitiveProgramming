#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 6011;

int n, l;
int words[MN];
int f[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    // input
    cin >> n >> l;
    for (int i = 1; i <= n; i++) {
        cin >> words[i];
    }

    // qhd
    for (int i = 1; i <= n; i++) {
        f[i] = l + 1;

        int sum = 0;  // tong do dai cac tu j+1 --> i
        for (int j = i - 1; j >= 0; j--) {
            sum += words[j + 1];
            if (sum > l) break;

            f[i] = min(f[i], max(f[j], l - sum));
        }
    }

    cout << f[n] << endl;
    return 0;
}
