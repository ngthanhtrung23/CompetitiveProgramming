#include "bits/stdc++.h"
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    if (n == 1) {
        cout << 1 << ' ' << 1 << endl;
        cout << -a[n-1] << endl;

        cout << 1 << ' ' << 1 << endl;
        cout << 0 << endl;

        cout << 1 << ' ' << 1 << endl;
        cout << 0 << endl;
        return 0;
    }

    cout << 1 << ' ' << n-1 << endl;
    for (int i = 0; i < n-1; i++) {
        cout << a[i] * (n-1) << ' ';
    }
    cout << endl;

    cout << n << ' ' << n << endl;
    cout << a[n-1] * -1 << endl;

    cout << 1 << ' ' << n << endl;
    for (int i = 0; i < n; i++) {
        if (i == n-1) cout << 0 << endl;
        else cout << -a[i] * n << ' ';
    }
}
