
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int res = 0;
    for (int i = 1; i < n; i+= 2) {
        res += a[i];
    }
    cout << res << endl;
    return 0;
}
