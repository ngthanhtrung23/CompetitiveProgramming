#include "bits/stdc++.h"

// given
//   x - y == diff
//   x + y == sum
// return: {x, y}
std::pair<int,int> solve(int diff, int sum) {
    return {(diff + sum) / 2, (sum - diff) / 2};
}
int32_t main() {
    int n, q; std::cin >> n >> q;

    // Check if a cell is inside chessboard
    auto inside = [&] (int u, int v) {
        return 1 <= u && u <= n
            && 1 <= v && v <= n;
    };
    while (q--) {
        int i, j, x, y; std::cin >> i >> j >> x >> y;

        if (i == x && j == y) { // same cell
            std::cout << 0 << '\n';
        } else if (i - j == x - y || i + j == x + y) { // same diagonal
            std::cout << 1 << '\n' << x << ' ' << y << '\n';
        } else if ((i + j) % 2 != (x + y) % 2) { // different colors -> impossible
            std::cout << -1 << '\n';
        } else {
            std::cout << 2 << '\n';
            {
                auto [a, b] = solve(i - j, x + y);
                if (inside(a, b)) {
                    std::cout << a << ' ' << b << '\n';
                    std::cout << x << ' ' << y << '\n';
                    continue;
                }
            }
            {
                auto [a, b] = solve(x - y, i + j);
                if (inside(a, b)) {
                    std::cout << a << ' ' << b << '\n';
                    std::cout << x << ' ' << y << '\n';
                }
            }
        }
    }
    return 0;
}
