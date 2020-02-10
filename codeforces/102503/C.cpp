#include "bits/stdc++.h"
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

int32_t main() {
    std::ios::sync_with_stdio(false);
    int ntest; std::cin >> ntest;
    while (ntest--) {
        int _; std::cin >> _;
        std::string s; std::cin >> s;
        size_t i = 0;
        std::tuple<int,int,int> res{0, 0, 0};
        while (i < s.size()) {
            if (s[i] == 'T') {
                std::get<0>(res) += 1;
                i += 2;
                continue;
            }
            if (s[i] == 's') {
                std::get<1>(res) += 1;
                i += 2;
                continue;
            }
            assert(s[i] == 'l');
            std::get<2>(res) += 1;
            i += 3;
        }

        std::cout << std::get<0>(res)
            << ' ' << std::get<1>(res)
            << ' ' << std::get<2>(res)
            << '\n';
    }
    return 0;
}
