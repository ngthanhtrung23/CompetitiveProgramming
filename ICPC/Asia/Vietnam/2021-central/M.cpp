#include "bits/stdc++.h"

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

const int MN = 100111;

struct DSU {
    int lab[MN];
    void init(int n) {
        REP(i,n+2) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

// Modified from anta's code
// Not tested with MOD > 10^9 + 7.
// Tested:
// - https://codeforces.com/gym/101383 - F (MOD = 1e9+7, +, *)

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
    constexpr ModInt(signed sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
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

modular fact[100111];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;
    DSU dsu;
    dsu.init(n);
    REP(i,m) {
        int u, v; cin >> u >> v;
        dsu.merge(u, v);
    }

    fact[0] = 1;
    FOR(i,1,n) fact[i] = fact[i-1] * i;

    modular res(0);
    REP(i,n) {
        if (dsu.lab[i] < -2) {
            res += fact[-dsu.lab[i]];
        }
    }
    cout << res << endl;

    return 0;
}
