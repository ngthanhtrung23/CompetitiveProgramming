#include <bits/stdc++.h>

void print(int x1, int y1, int x2, int y2, int x3, int y3) {
    std::cout << 2 << ' '
        << x1 << ' ' << y1 << ' ' 
        << x2 << ' ' << y2 << ' ' 
        << x3 << ' ' << y3 << '\n';
}

void solve() {
    int m; std::cin >> m; assert(1 <= m);
    int n; std::cin >> n;

    std::cout << 3*n << '\n';
    while (n--) {
        int x, y; std::cin >> x >> y;

        int x2 = x - 1; if (x2 < 0) x2 = x + 1;
        int y2 = y - 1; if (y2 < 0) y2 = y + 1;

        print(x2, y, x, y, x, y2);
        print(x, y, x2, y, x2, y2);
        print(x, y, x, y2, x2, y2);
    }
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int ntest;
    std::cin >> ntest;
    while (ntest--) {
        solve();
    }
    return 0;
}
