#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int get(int n, int k) {
    // a + b = n
    // a - b = k
    // a >= b

    if (n <= k) return 1;
    if ((n + k) % 2) return 1;

    int a = (n + k) / 2;
    int b = n - a;

    return get(a, k) + get(b, k);
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, k;
    while (cin >> n >> k) cout << get(n, k) << endl;
    return 0;
}
