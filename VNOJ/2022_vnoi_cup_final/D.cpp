#include "bits/stdc++.h"
#define int long long

std::vector<int> p10;

void init(int n) {
    p10.resize(n);
    p10[0] = 1 % n;
    for (int i = 1; i < n; i++) {
        p10[i] = p10[i-1] * 10 % n;
    }
}

void done() {
    int res; std::cin >> res;
    assert(res == 1);
}

void small(int n) {
    std::cout << "1 0" << std::endl;

    std::set<int> empty;
    for (int i = 1; i < n; i++) {
        empty.insert(i);
    }

    int nturn = n / 2;
    while (nturn--) {
        int pos, digit; std::cin >> pos >> digit;
        --pos;
        empty.erase(pos);

        if (n == 2) {
            break;
        }

        int i = *empty.begin();
        empty.erase(i);
        std::cout << (i+1) << ' ' << 0 << std::endl;
    }
    done();
}

void big(int n) {
    std::cout << n << " 0" << std::endl;

    std::vector<std::set<int>> moves(n);
    for (int i = 0; i < n-1; i++) {
        moves[p10[i]].insert(i);
    }

    int mid = (n - 1) / 2;
    int nturn = n / 2;
    while (nturn--) {
        int pos, digit; std::cin >> pos >> digit;
        --pos;

        moves[p10[pos]].erase(pos);

        if (p10[mid] == 1) {
            // find i: 10^i == 10^pos
            // -> print (i, 9 - digit)
            int need = p10[pos];
            assert(!moves[need].empty());

            int i = *moves[need].begin();
            moves[need].erase(i);

            std::cout << (i+1) << ' ' << 9 - digit << std::endl;
        } else {
            // find i: 10^i == -10^pos
            // -> print (i, digit)
            int need = (n - p10[pos]) % n;
            assert(!moves[need].empty());

            int i = *moves[need].begin();
            moves[need].erase(i);

            std::cout << (i+1) << ' ' << digit << std::endl;
        }
    }
    done();
}

int32_t main() {
    std::ios::sync_with_stdio(0);
    int ntest; std::cin >> ntest;
    while (ntest--) {
        int n; std::cin >> n;
        init(n);
        if (n == 2 || n == 5) small(n);
        else big(n);
    }
    return 0;
}
