#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int solve(vector< pair<int,int> > rects) {
    sort(rects.begin(), rects.end());

    for (int i = SZ(rects) - 1; i >= 0; i--) {
        int max_second = -1;
        for (int j = i + 1; j < SZ(rects); j++) {
            max_second = max(rects[j].second, max_second);
        }
        if (max_second >= rects[i].second) {
            rects.erase(rects.begin() + i);
        }
    }

    int res = 0;
    for (int i = 0; i < SZ(rects); i++) {
        int last = (i == 0) ? 0 : rects[i-1].first;

        res += (rects[i].first - last) * rects[i].second;
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int a[3], b[3];
    while (cin >> a[0] >> b[0] >> a[1] >> b[1] >> a[2] >> b[2]) {
        if (a[0] == 0) break;

        int res = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
        for (int r1 = 0; r1 < 2; r1++) {
            for (int r2 = 0; r2 < 2; r2++) {
                res = min(res, solve({
                    {a[0], b[0]},
                    {a[1], b[1]},
                    {a[2], b[2]},
                }));

                swap(a[2], b[2]);
            }
            swap(a[1], b[1]);
        }
        cout << res << endl;
    }
    return 0;
}
