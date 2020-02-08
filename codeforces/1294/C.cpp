#include "bits/stdc++.h"
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

void solve(int n) {
    int a = -1, b = -1;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            n /= i;
            if (a < 0) {
                a = i;
            } else {
                assert(b < 0);
                b = i;
                assert(a < b);
                if (n > b) {
                    std::cout << "YES\n" << a << ' ' << b << ' ' << n << '\n';
                } else {
                    std::cout << "NO\n";
                }
                return;
            }
        }
    }
    std::cout << "NO\n";
}

int32_t main() {
    std::ios::sync_with_stdio(false);

    int ntest; std::cin >> ntest;
    while (ntest--) {
        int n; std::cin >> n;

        solve(n);
    }
    return 0;
}
