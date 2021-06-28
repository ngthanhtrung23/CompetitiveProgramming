#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

vector<int> get_digits(int n) {
    vector<int> res;
    while (n > 0) {
        res.push_back(n % 10);
        n /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int f1[22][2];
int count1(int length, vector<int> digits_k) {
    int n_digit_of_k = SZ(digits_k);

    // append 0 to end of digits_k
    for (int i = 0; i <= length; i++) {
        digits_k.push_back(0);
    }

    memset(f1, 0, sizeof f1);
    f1[0][0] = 1;
    for (int i = 0; i < length; i++) {
        for (int lower = 0; lower < 2; lower++) {
            for (int cur = 0; cur < 10; cur++) {
                if (i == 0 && cur == 0) continue;
                if (!lower && cur > digits_k[i]) continue;

                int lower2 = lower || (cur < digits_k[i]);
                f1[i+1][lower2] += f1[i][lower];
            }
        }
    }

    int res = f1[length][1];
    if (length < n_digit_of_k) {
        res += f1[length][0];
    }
    return res;
}

int f2[22][2][2];
int count2(int length, vector<int> digits_n, vector<int> digits_k) {
    int n_digit_of_k = SZ(digits_k);

    // append 0 to end of digits_k
    for (int i = 0; i <= length; i++) {
        digits_k.push_back(0);
    }

    memset(f2, 0, sizeof f2);
    f2[0][0][0] = 1;

    for (int i = 0; i < length; i++) {
        for (int ln = 0; ln < 2; ln++) {
            for (int lk = 0; lk < 2; lk++) {
                for (int cur = 0; cur < 10; cur++) {
                    if (i == 0 && cur == 0) continue;
                    if (!ln && cur > digits_n[i]) continue;
                    if (!lk && cur > digits_k[i]) continue;

                    // next state
                    int ln2 = ln || (cur < digits_n[i]);
                    int lk2 = lk || (cur < digits_k[i]);
                    f2[i+1][ln2][lk2] += f2[i][ln][lk];
                }
            }
        }
    }

    int res = f2[length][1][1];
    if (length < n_digit_of_k) {
        res += f2[length][1][0];
    }
    return res;
}

// so luong so:
// - gia tri < n
// - thu tu tu dien < k
int get(int n, int k) {
    auto digits_n = get_digits(n);
    auto digits_k = get_digits(k);

    int res = 0;
    for (int length = 1; length <= SZ(digits_n); length++) {
        if (length < SZ(digits_n)) {
            res += count1(length, digits_k);
        } else {
            res += count2(length, digits_n, digits_k);
        }
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int k, m;
        cin >> k >> m;
        int MAX_K = 1e9;
        assert(1 <= k && k <= MAX_K);
        assert(1 <= m && m <= MAX_K);

        const int INF = 1e18;
        int left = k, right = INF, res = right;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (get(mid + 1, k) >= m - 1) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (res == INF) res = 0;
        else if (get(res + 1, k) != m - 1) res = 0;
        cout << res << endl;
    }
    return 0;
}
