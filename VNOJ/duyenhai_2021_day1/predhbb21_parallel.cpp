#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    while (true) {
        vector<int> a(12);
        bool all0 = true;
        for (int& x : a) {
            cin >> x;
            all0 &= x == 0;
        }
        if (all0) break;

        sort(a.begin(), a.end());

        cout << (((a[0] == a[3])
                && (a[4] == a[7])
                && (a[8] == a[11])) ? "yes" : "no") << endl;
    }
    return 0;
}
