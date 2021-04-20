#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int reverse(int n) {
    int res = 0;
    while (n > 0) {
        res = res * 10 + n % 10;
        n /= 10;
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    assert(reverse(123) == 321);
    assert(reverse(1000) == 1);

    int l, r;
    while (cin >> l >> r) {
        int cnt = 0;
        for (int i = l; i <= r; i++) {
            if (__gcd(i, reverse(i)) == 1) {
                cnt ++;
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}
