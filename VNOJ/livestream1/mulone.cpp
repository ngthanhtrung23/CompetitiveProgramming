#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;

        string res = "";
        int remainder = 0;
        for (int i = 1; i <= 2*n-1; i++) {
            // i = n+1 -> n-1
            // i = n+2 -> n-2
            int ones = (i <= n) ? i : (n - (i-n));

            int cur = ones + remainder;
            res += (char) (cur % 10 + '0');
            remainder = cur / 10;
        }
        while (remainder > 0) {
            res += (char) (remainder % 10 + '0');
            remainder /= 10;
        }

        reverse(res.begin(), res.end());
        cout << res << endl;
    }
    return 0;
}

/*
    11111
   x11111
    -----
    11111
   11111
  11111
 11111
11111
---------
 */
