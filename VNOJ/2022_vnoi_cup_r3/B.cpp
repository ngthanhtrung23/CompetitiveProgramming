#include "bits/stdc++.h"

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    std::string s; std::cin >> s;
    std::vector<int> positions;
    for (int i = 1; i < n; i++) {
        if (s[i-1] == '(' && s[i] == ')') {
            positions.push_back(i);
        }
    }
    positions.push_back(n);

    while (q--) {
        int l, r; std::cin >> l >> r;
        --l; --r;
        auto last = std::upper_bound(positions.begin(), positions.end(), r);
        auto first = std::upper_bound(positions.begin(), positions.end(), l);

        std::cout << last - first << std::endl;
    }
    return 0;
}
