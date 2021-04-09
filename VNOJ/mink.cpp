#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define left akjscjlac
#define right kajsclkjacoijq

const int INF = 1000111000;
const int MN = 40111;
int a[MN], left[MN], right[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n, k; cin >> n >> k;
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = n; i <= n+k; i++) a[i] = INF;
        
        // 0..k-1
        // k..2k-1
        for (int i = 0; i < n; i++) {
            if (i % k == 0) {
                left[i] = a[i];
            } else {
                left[i] = min(left[i-1], a[i]);
            }
        }
        for (int i = n-1; i >= 0; i--) {
            if (i == n-1 || i % k == k-1) {
                right[i] = a[i];
            } else {
                right[i] = min(right[i+1], a[i]);
            }
        }

        for (int l = 0, r = k-1; r < n; l++, r++) {
            cout << min(right[l], left[r]) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
