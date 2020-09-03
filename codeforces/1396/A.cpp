#include "bits/stdc++.h"
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    const auto f = [&a](int l, int r, int mult) {
        cout << l << ' ' << r << '\n';
        for (int i = l; i <= r; i++) {
            cout << a[i-1] * mult << ' ';
        }
        cout << '\n';
    };

    if (n == 1) {
        f(1, 1, -1);
        f(1, 1, 0);
        f(1, 1, 0);
        return 0;
    }

    f(1, n-1, n-1);
    f(n, n, n-1);
    f(1, n, -n);
}
