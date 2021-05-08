/**
 * hinh thang: a, b, c, d
 *
 * 1. a = b
 * 2. c <= d
 * 3. a + b + c > d
 *
 * Truong hop:
 *
 * - c = d
 *   - a = b = c = d
 *   - c = d < a = b
 *
 * - c < d
 *   - c < d = a = b
 *   - c = a = b < d
 *
 *   - c < d < a = b
 *   - c < a = b < d
 *   - a = b < c < d
 */

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int C[5011][5];

void init() {
    C[0][0] = 1;
    for (int i = 1; i <= 5000; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= min(4LL, i); j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}

int n;
pair<int,int> a[5011]; // {value, cummulative count}

int getCount(int l, int r) {
    return a[r].second - a[l - 1].second;
}

int solve() {
    int res = 0;

    // a = b = c = d
    for (int i = 1; i <= n; i++) {
        int cnt = getCount(i, i);
        res += C[cnt][4];
    }

    // c = d < a = b
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            int cnt1 = C[getCount(i, i)][2];
            int cnt2 = C[getCount(j, j)][2];

            res += cnt1 * cnt2;
        }
    }

    // c < d = a = b
    for (int c = 1; c <= n; c++) {
        for (int dab = c + 1; dab <= n; dab++) {
            int cnt_c = getCount(c, c);
            int cnt_dab = getCount(dab, dab);

            res += cnt_c * C[cnt_dab][3];
        }
    }

    // c = a = b < d
    for (int cab = 1; cab <= n; cab++) {
        for (int d = cab + 1; d <= n; d++) {
            if (a[cab].first * 3 <= a[d].first) continue;

            int cnt_cab = getCount(cab, cab);
            int cnt_d = getCount(d, d);

            res += C[cnt_cab][3] * cnt_d;
        }
    }

    // c < d < a = b
    for (int c = 1; c <= n; c++) {
        for (int ab = c + 2; ab <= n; ab++) {
            int cnt_c = getCount(c, c);
            int cnt_d = getCount(c + 1, ab - 1);
            int cnt_ab = getCount(ab, ab);

            res += cnt_c * cnt_d * C[cnt_ab][2];
        }
    }

    // c < a = b < d
    for (int ab = 2; ab <= n-1; ab++) {
        int max_d = ab + 1;
        for (int c = 1; c < ab; c++) {
            while (max_d < n && a[max_d + 1].first < a[c].first + a[ab].first * 2) {
                max_d++;
            }

            if (a[max_d].first < a[c].first + a[ab].first * 2) {
                res += getCount(c, c) * C[getCount(ab, ab)][2] * getCount(ab + 1, max_d);
            }
        }
    }

    // a = b < c < d
    for (int ab = 1; ab <= n-2; ab++) {
        int max_d = ab + 2;
        for (int c = ab + 1; c < n; c++) {
            while (max_d < n && a[max_d + 1].first < a[c].first + a[ab].first * 2) {
                max_d++;
            }

            if (max_d > c && a[max_d].first < a[c].first + a[ab].first * 2) {
                res += C[getCount(ab, ab)][2] * getCount(c, c) * getCount(c + 1, max_d);
            }
        }
    }

    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    init();

    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;

        map<int,int> cnt;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            cnt[x] += 1;
        }

        n = 0;
        for (auto [val, c] : cnt) {
            a[++n] = {val, c};
            a[n].second += a[n-1].second;
        }

        // for (int i = 1; i <= n; i++) cout << a[i].first << ' ' << a[i].second << endl;

        cout << solve() << endl;
    }
    return 0;
}
