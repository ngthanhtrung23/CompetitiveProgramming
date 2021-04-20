#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 100111;

int a[MN], b[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        sort(a+1, a+n+1);
        sort(b+1, b+n+1);

        a[n+1] = 1000111000;
        b[n+1] = 1000111000;

        int res = 2000111000;
        for (int i = 1; i <= n; i++) {
            int j = lower_bound(b+1, b+n+2, -a[i]) - b;
            
            if (j <= n) {
                res = min(res, abs(a[i] + b[j]));
            }
            if (j > 1) {
                --j;
                res = min(res, abs(a[i] + b[j]));
            }
        }
        cout << res << endl;
    }
    return 0;
}
