#include "bits/stdc++.h"
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

int32_t main() {
    std::ios::sync_with_stdio(false);
    size_t n; std::cin >> n;
    for (size_t i = 0; i < n; i++) {
        std::string s; std::cin >> s;
        std::cout << s << ": F\n";
    }
    return 0;
}
