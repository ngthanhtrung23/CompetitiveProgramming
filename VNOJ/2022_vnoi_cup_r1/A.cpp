#include "bits/stdc++.h"

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n; std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int& x : a) std::cin >> x;
    for (int& y : b) std::cin >> y;

    if (a.back() == b[0]) {
        std::cout << 'b';
        for (int i = 0; i < n; i++) std::cout << 'a';
        for (int i = 1; i < n; i++) std::cout << 'b';
        std::cout << std::endl;
    } else {
        for (int i = 0; i < n; i++) std::cout << 'a';
        for (int i = 0; i < n; i++) std::cout << 'b';
        std::cout << std::endl;
    }
    return 0;
}
