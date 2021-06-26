#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

// f(i, bad, last_digit, lower, positive)
int f[22][22][10][2][2];
int d[22];

int get(int a, int D, int k) {
    // khoi tao mang chu so cua a
    vector<int> digits;
    while (a > 0) {
        digits.push_back(a % 10);
        a /= 10;
    }
    for (int i = 1; i <= SZ(digits); i++) {
        d[i] = digits[SZ(digits) - i];
    }

    /*
    for (int i = 1; i <= SZ(digits); i++) {
        cout << d[i];
    }
    cout << endl;
    */

    // goi dp(...)
    memset(f, 0, sizeof f);
    f[0][0][0][0][0] = 1;

    for (int i = 0; i < SZ(digits); i++) {
        for (int bad = 0; bad <= i; bad++) {
            for (int last = 0; last < 10; last++) {
                for (int lower = 0; lower < 2; lower++) {
                    for (int positive = 0; positive < 2; positive++) {
                        for (int next = 0; next < 10; next++) {
                            if (!lower && next > d[i+1]) continue;

                            // (i+1, bad2, last2, lower2, positive2)
                            int bad2 = bad;
                            if (positive && abs(last - next) <= D) ++bad2;
                            int last2 = next;
                            int lower2 = lower || (next < d[i+1]);
                            int positive2 = positive || next > 0;

                            f[i+1][bad2][last2][lower2][positive2] +=
                                f[i][bad][last][lower][positive];
                        }
                    }
                }
            }
        }
    }

    int res = 0;
    for (int bad = 0; bad <= k; bad++) {
        for (int last = 0; last < 10; last++) {
            res += f[SZ(digits)][bad][last][1][1];
        }
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int a, b, D, k;
    while (cin >> a >> b >> D >> k) {
        cout << get(b + 1, D, k) - get(a, D, k) << endl;
    }
    return 0;
}

// k = 0
// 1 -> 9; 11
