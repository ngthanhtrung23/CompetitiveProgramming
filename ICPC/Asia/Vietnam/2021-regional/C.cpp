#include "bits/stdc++.h"

#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define SZ(x) ((int)(x).size())
using namespace std;

const int MN = 200111;
struct PolygonRegion {  // everything is 0-based index
    int n;
    set<int> vertices;
    vector< pair<int,int> > diagonals;
    vector< vector<int> > regions;

    PolygonRegion(int _n) : n(_n) {
        vertices.clear();
        REP(i,n) vertices.insert(i);
        diagonals.clear();
    }

    void addEdge(int a, int b) {
        assert(a != b);
        if (a > b) swap(a, b);
        assert(a + 1 != b);
        if (a == n-1) assert(b != 0);

        diagonals.emplace_back(b - a, a);
    }

    void init() {
        diagonals.emplace_back(n-1, 0);
        regions.clear();

        sort(diagonals.begin(), diagonals.end());
        REP(idiag,SZ(diagonals)) {
            auto diagonal = diagonals[idiag];

            // (s, t) = current diagonal
            int s = diagonal.second;
            int t = s + diagonal.first;

            // extract polygon
            auto it = vertices.find(s); ++it;
            vector<int> cur;
            cur.push_back(s);
            while (true) {
                if (*it == t) break;
                cur.push_back(*it);
                vertices.erase(it++);
            }
            cur.push_back(t);

            regions.push_back(cur);
        }
    }
};

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

const int MOD = 998244353;
using modular = ModInt<MOD>;

std::ostream& operator << (std::ostream& cout, const modular& m) {
    cout << m.x;
    return cout;
}
std::istream& operator >> (std::istream& cin, modular& m) {
    cin >> m.x;
    return cin;
}

modular fact[MN], inv_fact[MN], catalan[MN];

modular C(int n, int k) {
    assert(0 <= k && k <= n && n < MN);
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    fact[0] = 1;
    for (int i = 1; i < MN; i++) {
        fact[i] = fact[i-1] * i;
    }
    for (int i = 0; i < MN; i++) {
        inv_fact[i] = fact[i].inv();
    }
    for (int i = 0; i <= 100000; i++) {
        modular inv_n_1 = modular(i+1).inv();
        catalan[i] = C(2*i, i) * inv_n_1;
    }

    int n, k, m; cin >> n >> k >> m;
    PolygonRegion p(n);
    while (k--) {
        int u, v; cin >> u >> v;
        --u; --v;
        p.addEdge(u, v);
    }
    p.init();

    modular color = modular(m) * power(modular(m-1), n-3);
    modular res = 1;
    for (const auto& region : p.regions) {
        int sz = region.size();
        res *= catalan[sz - 2];
    }
    cout << color << ' ' << res << endl;

    return 0;
}
