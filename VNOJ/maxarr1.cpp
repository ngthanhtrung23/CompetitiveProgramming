#include "bits/stdc++.h"
using namespace std;

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 100111;
int a[MN], f[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    a[0] = 0;
    f[0] = 0;
    a[1] = 1;
    f[1] = 1;
    for (int i = 2; i <= 100000; i++) {
        if (i % 2 == 0) {
            a[i] = a[i/2];
        } else {
            a[i] = a[i/2] + a[i/2 + 1];
        }
        f[i] = max(f[i-1], a[i]);
    }
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        int n; scanf("%d", &n);
        printf("%d\n", f[n]);
    }
    return 0;
}
