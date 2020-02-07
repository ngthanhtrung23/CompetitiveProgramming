#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif
#include<bits/stdc++.h>
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define PR0(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) std::cerr << A[_] << ' '; std::cerr << std::endl; }

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
	static const int Mod = MOD;
	unsigned x;
	ModInt() : x(0) { }
	ModInt(signed sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
	ModInt(signed long long sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
	int get() const { return (int)x; }

	ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
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
};
const int MOD = 1e9 + 7;
using modular = ModInt<MOD>;

std::ostream& operator << (std::ostream& cout, const modular& m) {
    cout << m.x;
    return cout;
}
std::istream& operator << (std::istream& cin, modular& m) {
    cin >> m.x;
    return cin;
}

int main() {
    freopen("meganim.in", "r", stdin);
    freopen("meganim.out", "w", stdout);

    int n;
    long long limit;
    std::cin >> n >> limit;
    
    const int NBIT = 62;
    std::bitset<NBIT> bits_rev(limit + 1);
    auto str = bits_rev.to_string();
    std::reverse(str.begin(), str.end());
    std::bitset<NBIT> bits(str);

    std::vector<std::vector<modular>> C(n+1, std::vector<modular> (n+1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    std::vector<std::vector<modular>> g(n + 1, std::vector<modular> (2, 0));
    // g[i][val] = how many ways of setting i bits, so that the xor-sum is equal to val.
    g[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        g[i][0] = g[i-1][0] + g[i-1][1];
        g[i][1] = g[i-1][0] + g[i-1][1];
    }

    std::vector<std::vector<modular>> f(NBIT, std::vector<modular> (n + 1, 0));
    // f[i][j] = how many ways to make the sum xor of first i bits equal to 0
    //           j = how many number less than `limit`.
    f[0][0] = 1;
    for (int pos = 0; pos < NBIT-1; pos++) {
        for (int less = 0; less <= n; less++) {
            int equal = n - less;
            for (int equal_to_less = 0; equal_to_less <= (bits[pos+1] == 0 ? 0 : equal); equal_to_less++) {
                if (bits[pos+1] == 0) {
                    assert(equal_to_less == 0);
                }
                int stay_equal = equal - equal_to_less;
                int cur_sum = stay_equal * bits[pos + 1] % 2;

                f[pos + 1][less + equal_to_less] +=
                    f[pos][less] * C[equal][equal_to_less] * g[less][cur_sum];
            }
        }
    }

    std::cout << f[NBIT-1][n] << std::endl;
}
