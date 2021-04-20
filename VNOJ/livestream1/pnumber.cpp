#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

bool isPrime[200111];

int32_t main() {
    ios::sync_with_stdio(0);

    memset(isPrime, true, sizeof isPrime);
    // sieve
    for (int i = 2; i*i <= 200000; i++) {
        if (!isPrime[i]) continue;

        for (int j = i*i; j <= 200000; j += i) {
            isPrime[j] = false;
        }
    }
    isPrime[1] = false;

    int l, r;
    while (cin >> l >> r) {
        for (int i = l; i <= r; i++) {
            if (isPrime[i]) {
                cout << i << '\n';
            }
        }
    }
    return 0;
}
