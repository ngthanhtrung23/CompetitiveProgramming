
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 11;
int f[MN][MN];

int32_t main() {
    ios::sync_with_stdio(0);
    // qhd
    f[2][1] = 1;
    f[2][2] = 2;
    for (int i = 3; i <= 10; i++) {
        for (int g = 1; g <= i; g++) {
            f[i][g] = f[i-1][g] * g;
            if (g - 1 >= 1) {
                f[i][g] += f[i-1][g-1] * g;
            }
        }
    }

    // input & output
    int n;
    while (cin >> n) {
        if (n < 0) break;

        cout << std::accumulate(f[n]+1, f[n]+n+1, 0) << endl;
    }
    return 0;
}
