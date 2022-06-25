#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        string t; cin >> t;
        string r = t;
        reverse(r.begin(), r.end());

        int save_left = -1;
        int save_right = -2;

        int left = 0;
        int mid = SZ(t) / 2 + SZ(t) % 2;
        // SZ = 3 -> mid = 2
        // SZ = 4 -> mid = 2
        while (left < mid) {
            if (t[left] != r[left]) {
                ++left;
                continue;
            }

            int right = left;
            while (right + 1 < SZ(t) && t[right + 1] == r[right + 1]) {
                ++right;
            }
            if (right - left + 1 > save_right - save_left + 1) {
                save_left = left;
                save_right = right;
            }

            left = right + 1;
        }

        assert(save_left >= 0);
        cout << t.substr(save_left, save_right - save_left + 1) << '\n';
    }
    return 0;
}
