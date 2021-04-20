#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    int a, b, c;
    while (cin >> a >> b >> c) {
        vector<int> cnt(100, 0);

        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= b; j++) {
                for (int k = 1; k <= c; k++) {
                    cnt[i + j + k]++;
                }
            }
        }

        cout << max_element(cnt.begin(), cnt.end()) - cnt.begin() << '\n';
    }
    return 0;
}
