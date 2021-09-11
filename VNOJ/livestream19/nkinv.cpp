#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 60111;
int bit[MN];

void update(int u) {
    for (int x = u; x < MN; x += x & -x) {
        bit[x]++;
    }
}
int get(int u) {
    int res = 0;
    for (int x = u; x > 0; x -= x & -x) {
        res += bit[x];
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int res = 0;
    for (int i = n-1; i >= 0; i--) {
        res += get(a[i] - 1);

        update(a[i]);
    }
    cout << res << endl;
    return 0;
}
