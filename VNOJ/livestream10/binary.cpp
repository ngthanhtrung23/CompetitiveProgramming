#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int f[44][2][44][2], n[44];

int32_t main() {
    ios::sync_with_stdio(0);
    int N, K;
    while (cin >> N >> K) {
        vector<int> bits;
        while (N > 0) {
            bits.push_back(N % 2);
            N /= 2;
        }
        if (bits.empty()) bits.push_back(0);

        if (K > SZ(bits)) {
            cout << 0 << endl;
            continue;
        }

        // init bit seq
        for (int i = 1; i <= bits.size(); i++) {
            n[i] = bits[SZ(bits) - i];
        }
        /*
        for (int i = 1; i <= bits.size(); i++) {
            cout << n[i];
        }
        cout << endl;
        */

        // DP
        memset(f, 0, sizeof f);
        f[0][0][0][0] = 1;
        // f(i, lower, k, > 0)

        for (int i = 0; i < bits.size(); i++) {
            for (int lower = 0; lower <= 1; lower++) {
                for (int k = 0; k <= i; k++) {
                    for (int positive = 0; positive <= 1; positive++) {
                        for (int digit = 0; digit <= 1; digit++) {
                            int cur = f[i][lower][k][positive];

                            if (!lower && digit > n[i+1]) {
                                continue;
                            }
                            int lower2 = lower || (digit < n[i+1]);
                            int k2 = k;
                            if (positive && digit == 0) k2++;
                            int positive2 = positive || digit > 0;

                            f[i+1][lower2][k2][positive2] +=
                                f[i][lower][k][positive];
                        }
                    }
                }
            }
        }

        int res = 0;
        for (int lower = 0; lower < 2; lower++) {
            res += f[bits.size()][lower][K][1];
        }
        if (K == 1) {
            ++res;
        }
        cout << res << endl;
    }
    return 0;
}
