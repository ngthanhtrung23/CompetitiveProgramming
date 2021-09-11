
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, L;
    cin >> n >> L;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    // binary search:
    // - find maximum h: can create h a[i] >= h

    auto cnt = [&] (int h) {
        int res = 0;
        int equal_h_1 = 0;
        for (int x : a) {
            if (x >= h) ++res;
            if (x == h-1) ++equal_h_1;
        }

        res += min(equal_h_1, L);
        return res;
    };

    int left = 0, right = n, res = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (cnt(mid) >= mid) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << res << endl;
    return 0;
}
