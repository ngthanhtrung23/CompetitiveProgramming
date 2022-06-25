/**
 * k = 0 --> 2^n
 * moi so: 2 cach (chia vao 2 nhom)
 *
 * {4, 8}
 * n = 10
 *
 * 1 -> 2
 * 2 -> 2
 * 3 -> 1
 * 4 -> 2
 * 5 -> 1
 * 6 -> 1
 * 7 -> 1
 * 8 -> 2
 * 9 -> 2
 * 10 -> 2
 *
 * x -> x/2+1 -> x-1: 1 cach
 */

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MOD = 1e9 + 7;

int power(int x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    int mid = power(x, k / 2);
    mid = mid * mid % MOD;

    if (k % 2) return mid * x % MOD;
    return mid;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, k;
    while (cin >> n >> k && n && k) {
        vector<int> xs(k);
        for (int& x : xs) {
            cin >> x;
        }
        sort(xs.begin(), xs.end());

        int cnt2 = n;
        for (int x : xs) {
            if (x == 1) {
                continue;
            }

            // [x/2+1, x-1], [1, n]
            int ub = min(n, x - 1);
            cnt2 -= ub - x/2;
        }
        cout << power(2, cnt2) << endl;
    }
    return 0;
}
