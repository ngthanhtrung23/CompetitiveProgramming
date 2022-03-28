#include <bits/stdc++.h>
using namespace std;

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n; std::cin >> n;
    std::cout << (n-1) * (n-2) / 2 << ".0000" << std::endl;
    for (int i = 2; i <= n; i++) {
        std::cout << 1 << ' ' << i << std::endl;
    }
    return 0;
}
