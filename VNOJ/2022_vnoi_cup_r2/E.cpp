#include "bits/stdc++.h"
using namespace std;

// modint
inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
    unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
    asm(
        "divl %4; \n\t"
        : "=a" (d), "=d" (m)
        : "d" (xh), "a" (xl), "r" (y)
    );
#else
    __asm {
        mov edx, dword ptr[xh];
        mov eax, dword ptr[xl];
        div dword ptr[y];
        mov dword ptr[d], eax;
        mov dword ptr[m], edx;
    };
#endif
    out_d = d; out_m = m;
}

template<int MOD>
struct ModInt {
    unsigned x;

    constexpr ModInt() : x(0) { }
    constexpr ModInt(signed long long sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }

#define COMPAREOP(OP) bool constexpr operator OP(ModInt b) const { return x OP b.x; }
    COMPAREOP(==) COMPAREOP(!=) COMPAREOP(<) COMPAREOP(>) COMPAREOP(<=) COMPAREOP(>=)
#undef COMPAREOP

    ModInt operator-() const { return ModInt(x ? MOD - x : 0); }

    ModInt constexpr& operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
    ModInt constexpr& operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
    ModInt &operator*=(ModInt that) {
        unsigned dummy;
        fasterLLDivMod((unsigned long long)x * that.x, MOD, dummy, x);
        return *this;
    }
    ModInt operator*(ModInt that) const {
        ModInt res;
        unsigned dummy;
        fasterLLDivMod((unsigned long long)x * that.x, MOD, dummy, res.x);
        return res;
    }
    ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
    ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }

    // Below: copied from user202729_, not tested.
    ModInt inv() const {
        int a = x, b = MOD, ax = 1, bx = 0;
        while (b) {
            int q = a/b, t = a%b;
            a = b; b = t;
            t = ax - bx*q;
            ax = bx; bx = t;
        }
        assert(a == 1);
        if (ax < 0) ax += MOD;
        return ax;
    }
    ModInt& operator /= (ModInt m) { return (*this) *= m.inv(); }
    ModInt operator / (ModInt that) const { return ModInt(*this) /= that; }
};

template<int MOD>
ModInt<MOD> power(ModInt<MOD> n, long long k) {
    if (k == 0) return ModInt<MOD> (1);
    ModInt<MOD> res(1);
    while (k > 0) {
        if (k & 1) res = res * n;
        n = n * n;
        k >>= 1;
    }
    return res;
}

const int MOD = 1e9 + 7;
using modular = ModInt<MOD>;

std::ostream& operator << (std::ostream& cout, const modular& m) {
    cout << m.x;
    return cout;
}
std::istream& operator >> (std::istream& cin, modular& m) {
    cin >> m.x;
    return cin;
}

modular f[111][111];

void solve() {
    std::string s; std::cin >> s;
    int n = (int) s.size();

    // returns true if [l1, r1] should be after [l2, r2]
    auto check = [&] (int l1, int r1, int l2, int r2) -> bool {
        auto s1 = s.substr(l1, r1 - l1 + 1);
        auto s2 = s.substr(l2, r2 - l2 + 1);

        return s2 + s1 <= s1 + s2;
    };

    for (int i = 0; i < n; i++) {
        f[i][0] = 1;
        for (int start = 1; start <= i; start++) {
            f[i][start] = 0;
            int j = start - 1;
            for (int prev = 0; prev <= j; prev++) {
                if (check(start, i, prev, j)) {
                    f[i][start] += f[j][prev];
                }
            }
        }
    }

    modular res = 0;
    for (int start = 1; start < n; start++) {
        res += f[n-1][start];
    }
    std::cout << res << '\n';
}

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int ntest; std::cin >> ntest;
    while (ntest--) {
        solve();
    }
    return 0;
}
