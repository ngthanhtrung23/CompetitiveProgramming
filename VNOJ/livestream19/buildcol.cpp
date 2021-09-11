
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int water(const vector<int>& h) {
    int n = SZ(h);

    // init maxLeft & maxRight
    vector<int> maxLeft(n);
    vector<int> maxRight(n);
    for (int i = 0; i < n; i++) {
        if (i == 0) maxLeft[i] = h[i];
        else maxLeft[i] = max(maxLeft[i-1], h[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        if (i == n-1) maxRight[i] = h[i];
        else maxRight[i] = max(maxRight[i+1], h[i]);
    }

    //
    int res = 0;
    for (int i = 1; i < n-1; i++) {
        int cur = min(maxLeft[i-1], maxRight[i+1]);
        if (cur < h[i]) continue;

        res += cur - h[i];
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    int n, need; cin >> n >> need;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    if (water(a) < need) {
        cout << -1 << endl;
        return 0;
    }

    // binary search
    int left = 0, right = (int) 2e9;
    int res = 0;
    while (left <= right) {
        int mid = (left + right) / 2;

        vector<int> cur(n);
        for (int i = 0; i < n; i++) {
            cur[i] = max(mid, a[i]);
        }
        if (water(cur) >= need) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << res << endl;
    return 0;
}

