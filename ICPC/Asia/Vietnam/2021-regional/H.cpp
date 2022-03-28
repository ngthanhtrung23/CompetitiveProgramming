#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int ntest; std::cin >> ntest;
    while (ntest--) {
        int n; std::cin >> n;
        for (int i = 0; i < n; i++) {
            int x, y; std::cin >> x >> y;
        }

        for (int turn = 0; ; turn = 1 - turn) {
            if (n < 2) {
                std::cout << (turn == 0 ? "Vuong" : "Hoang") << '\n';
                break;
            }
            n -= 2;
        }
    }
    return 0;
}
