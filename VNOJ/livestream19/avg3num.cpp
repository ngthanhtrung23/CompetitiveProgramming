// (a + b + c) / 3 == x
// a + b + c == 3*x

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int a, b, c, x; cin >> a >> b >> x;
    cout << (3*x - a - b) << endl;
    return 0;
}
