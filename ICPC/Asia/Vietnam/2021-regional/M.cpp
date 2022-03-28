/**
f[i]  = sum all num ending at i
      = f[i-1]*10 + (cnt[i-1] + 1)*a[i]

x -> (x*10 + a[i])^2
     100*x^2 + a[i]^2 + 20*a[i]*x
f2[i] = sum all num^2 ending at i
 */
#include "bits/stdc++.h"
using namespace std;

// ModInt
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

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    std::string s; std::cin >> s;
    int n = s.size();
    s = " " + s;

    std::vector<modular> a(n+1);
    for (int i = 1; i <= n; i++) {
        a[i] = modular(s[i] - '0');
    }

    std::vector<modular> f(n + 1);
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i-1] * 10 + a[i] * i;
    }

    std::vector<modular> f2(n + 1);
    f2[0] = 0;
    for (int i = 1; i <= n; i++) {
        f2[i] = f2[i-1] * 100
            + a[i] * a[i] * i
            + a[i] * 20 * f[i-1];
    }

    std::cout << accumulate(f2.begin(), f2.end(), modular{0}) << std::endl;
    return 0;
}
