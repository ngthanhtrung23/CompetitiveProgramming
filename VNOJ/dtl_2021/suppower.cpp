#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& cout, const pair<U, V>& p) {
    return cout << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator << (ostream& cout, const Con& con) {
    cout << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        cout << (it == beg ? "" : ", ") << *it;
    }
    return cout << '}';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& cout, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return cout << ")"; 
    else return print_tuple_utils<i + 1, T>(cout << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& cout, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(cout, t);
}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MOD[8] = {
    1000000007,  // 0
    1000000006,  // 1
    500000002,   // 2
    243900800,   // 3
    79872000,    // 4
    19660800,    // 5
    5242880,     // 6
    2097152,     // 7
};

const int MN = 10111;
int a[MN];

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

int power(int x, int k, int mod) {
    if (k == 0) return 1 % mod;

    unsigned res = 1 % mod;
    unsigned tmp;
    while (k > 0) {
        if (k & 1) {
            fasterLLDivMod(res * x, mod, tmp, res);
        }
        k >>= 1;
        x = x * x % mod;
    }
    return res;
}

int f[8][MN];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i];
        }

        int res = 0;
        FOR(j,1,n) {
            FORD(t,7,0) {
                FORD(i,j,1) { // n^2 * 8
                    // for large j - i, power tower becomes constant
                    // so we can reuse values from previous j
                    if (j - i > 40) break;
                    if (i == j) {
                        f[t][i] = a[j] % MOD[t];
                    } else if (t == 7) {
                        int k = f[7][i+1] % (MOD[7]/2);
                        k += MOD[7] / 2;
                        f[7][i] = power(a[i], k, MOD[7]);
                    } else {
                        int k = f[t+1][i+1] + MOD[t+1];
                        f[t][i] = power(a[i], k, MOD[t]);
                    }

                    assert(f[t][i] < MOD[t]);
                }
            }
            FORD(i,j,1) {
                res = (res + f[0][i]) % MOD[0];
            }
        }
        cout << res << endl;
        break;
    }
    return 0;
}
