#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    int n, m;
    while (cin >> n >> m) {
        vector<int> prices(m);
        for (int& x : prices) cin >> x;

        // cost = 1
        pair<int,int> res = {min(m, n), -1};

        sort(prices.begin(), prices.end());
        for (int i = 0; i < m; i++) {
            // cost = prices[i]

            res = max(res,
                    {prices[i] * min(n, m - i), -prices[i]});
        }

        cout << -res.second << ' ' << res.first << endl;
    }
    return 0;
}
