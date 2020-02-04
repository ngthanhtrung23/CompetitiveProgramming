#include<bits/stdc++.h>
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define PR(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; for(size_t i = 1, _n = n; i <= _n; i++) std::cerr << A[i] << ' '; std::cerr << std::endl; }
#define PR0(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; for(size_t i = 0, _n = n; i < _n; i++) std::cerr << A[i] << ' '; std::cerr << std::endl; }

struct Fenwick {
    Fenwick(int n) : n(n) {
        f.resize(n + 1);
    }

    // 1-based
    void update(int u, int delta) {
        for (; u <= n; u += u & -u) {
            f[u] += delta;
        }
    }

    // 1-based
    int64_t get(int u) {
        int64_t res = 0;
        for (; u > 0; u -= u & -u) {
            res += f[u];
        }
        return res;
    }

    // 1-based
    int64_t get(int u, int v) {
        return get(v) - get(u - 1);
    }

    std::vector<int64_t> f;
    int n;
};

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int ntest; std::cin >> ntest;
    std::vector<int> a(100111, 0);
    Fenwick fenwick(100111);
    while (ntest--) {
        int n, q; std::cin >> n >> q;

        while (q--) {
            int typ, x, y; std::cin >> typ >> x >> y;
            if (typ == 1) {
                assert(1 <= x && x <= n);
                int delta = y - a[x];
                fenwick.update(x, delta);
                a[x] = y;
            } else {
                assert(typ == 2);
                assert(1 <= x && x <= y && y <= n);
                std::cout << fenwick.get(x, y) << '\n';
            }
        }
    }
}
