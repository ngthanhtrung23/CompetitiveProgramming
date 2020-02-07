
/*
#pragma GCC optimize("O3")
#ifdef ONLINE_JUDGE
#pragma GCC target("avx,avx2,fma,popcount")
#endif
#pragma GCC optimize("unroll-loops")
*/
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

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

    explicit constexpr operator int() const { return x; }

	constexpr ModInt() : x(0) { }
	ModInt(signed sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
	ModInt(signed long long sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }

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
};
const int MOD = 1e9 + 7;
using modular = ModInt<MOD>;

std::ostream& operator << (std::ostream& cout, const modular& m) {
    cout << m.x;
    return cout;
}

int32_t main() {
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
        g[i][1] = g[i][0];
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
    return 0;
}
