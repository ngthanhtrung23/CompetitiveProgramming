#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int cost[33];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    cin >> cost[0];
    for (int i = 1; i <= 25; i++) {
        cost[i] = (cost[i-1] + 1) % 26;
    }

    int res = 0;
    for (char c : s) res += cost[c - 'a'];
    cout << res << endl;
    return 0;
}
