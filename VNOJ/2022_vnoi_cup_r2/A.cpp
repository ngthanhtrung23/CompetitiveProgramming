#include "bits/stdc++.h"
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // read input
    int n, m; std::cin >> n >> m;
    std::vector<std::pair<int,int>> a(n);
    for (auto& [l, r] : a) std::cin >> l >> r;

    // find tour with min_r and max_l
    int min_r = 0, max_l = 0;
    for (int i = 1; i < n; i++) {
        const auto [l, r] = a[i];
        if (r < a[min_r].second) {
            min_r = i;
        }
        if (l > a[max_l].first) {
            max_l = i;
        }
    }
    
    // if min_r < max_l -> has solution
    if (a[min_r].second < a[max_l].first) {
        std::cout << "YES\n" << 1+min_r << ' ' << 1+max_l << '\n';
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
