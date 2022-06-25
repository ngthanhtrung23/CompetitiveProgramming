#include "bits/stdc++.h"

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n; std::cin >> n;
    std::vector<int> a(n);
    const int MAX_V = 2000111;
    std::vector<int> cnt(MAX_V);
    for (int& x : a) {
        std::cin >> x;
        cnt[x]++;
    }

    std::vector<int> mult_cnt(MAX_V);
    for (int i = 1; i < MAX_V; i++) {
        for (int mult = i; mult < MAX_V; mult += i) {
            mult_cnt[i] += cnt[mult];
        }
    }

    for (int i = 0; i < n; i++) {
        int mult = mult_cnt[2*a[i]];
        std::cout << (mult * (mult - 1LL) / 2) << ' ';
    }
    std::cout << std::endl;
    return 0;
}
