#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    for (int test = 0; test < 2; test++) {
        vector<int> a(3);
        for (int& x : a) cin >> x;
        sort(a.begin(), a.end());
        cout << (a[0] + a[1] == a[2] ? "yes" : "no") << endl;
    }
    return 0;
}
