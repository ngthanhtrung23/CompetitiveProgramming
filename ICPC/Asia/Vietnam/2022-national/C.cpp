// template {{{
// CF pragma: https://codeforces.com/blog/entry/96344
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator << (ostream& out, const Con& con) {
    out << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        out << (it == beg ? "" : ", ") << *it;
    }
    return out << '}';
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_rand(long long r) {
    return uniform_int_distribution<long long> (0, r-1)(rng);
}
long long get_rand(long long l, long long r) {
    return uniform_int_distribution<long long> (l, r)(rng);
}

template<typename T>
vector<T> read_vector(int n) {
    vector<T> res(n);
    for (int& x : res) cin >> x;
    return res;
}

void solve();

template<typename T> void upMin(T& x, T val) { if (val < x) x = val; }
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}

// }}}
// Sieve {{{
// Tested:
// - (up to 5e8) https://judge.yosupo.jp/problem/enumerate_primes
typedef unsigned uint;

// NOTE: gP(n) is incorrect for even values of n
const uint64_t N = 2'200'000;
uint mark[N / 64 + 1];
// DO NOT USE gP(n) directly.
#define gP(n) (mark[(n)>>6]&(1<<(((n)>>1)&31)))
#define rP(n) (mark[(n)>>6]&=~(1<<(((n)>>1)&31)))

// prime indexed from 0
uint prime[200111], nprime;

void sieve() {
    memset(mark, -1, sizeof mark);
    uint i;
    uint sqrtN = (uint)sqrt((double) N) + 1;

    for (i = 3; i < sqrtN; i += 2) if (gP(i)) {
        uint i2 = i + i;
        for (uint j = i * i; j < N; j += i2) rP(j);
    }
    nprime = 0;
    prime[nprime++] = 2;
    for (i = 3; i < N; i += 2)
        if (gP(i)) prime[nprime++] = i;
}

bool is_prime_small(uint x) {
    if (x == 2) return true;
    if (x <= 1) return false;
    if (x % 2 == 0) return false;
    if (gP(x)) return true;
    return false;
}
// }}}
// Rabin miller {{{
inline unsigned mod_mult(unsigned a, unsigned b, unsigned m) {
  return (uint64_t)a*b%m;
}
 
unsigned mod_pow(unsigned a, uint64_t b, unsigned m) {
  unsigned ret = 1;
  for(;;) {
    if (b&1) ret = mod_mult(ret, a, m);
    if (!(b>>=1)) return ret;
    a = mod_mult(a, a, m);
  }
}
 
bool is_prime_32(unsigned n) {
  if (n <= 3) return (n >= 2);
  static const unsigned small[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
  };
  for (int i = 0; i < sizeof(small)/sizeof(unsigned); i++) {
    if (n%small[i] == 0) return n == small[i];
  }
 
  // Jaeschke93 showed that 2,7,61 suffice for n < 4,759,123,141.
  static const unsigned millerrabin[] = {2, 7, 61};
  unsigned s = n-1, r = 0;
  while (s%2 == 0) {s /= 2; r++;}
 
  for (int i = 0, j; i < sizeof(millerrabin)/sizeof(unsigned); i++) {
    unsigned md = mod_pow(millerrabin[i], s, n);
    if (md == 1) continue;
    for (j = 1; j < r; j++) {
      if (md == n-1) break;
      md = mod_mult(md, md, n);
    }
    if (md != n-1) return false;
  }
 
  return true;
}

inline uint64_t mod_mult64(uint64_t a, uint64_t b, uint64_t m) {
    return __int128_t(a) * b % m;
}
uint64_t mod_pow64(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t ret = (m > 1);
    for (;;) {
        if (b & 1) ret = mod_mult64(ret, a, m);
        if (!(b >>= 1)) return ret;
        a = mod_mult64(a, a, m);
    }
}

// Works for all primes p < 2^64
bool is_prime(uint64_t n) {
    if (n <= 3) return (n >= 2);
    if (n <= 4294967295ULL) return is_prime_32(n);
    static const uint64_t small[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
    };
    for (size_t i = 0; i < sizeof(small) / sizeof(uint64_t); ++i) {
        if (n % small[i] == 0) return n == small[i];
    }

    // Makes use of the known bounds for Miller-Rabin pseudoprimes.
    static const uint64_t millerrabin[] = {
        2, 3, 5,
    };
    static const uint64_t A014233[] = {  // From OEIS.
        2047LL, 1373653LL, 25326001LL, 3215031751LL, 2152302898747LL,
        3474749660383LL, 341550071728321LL, 341550071728321LL,
        3825123056546413051LL, 3825123056546413051LL, 3825123056546413051LL, 0,
    };
    uint64_t s = n-1, r = 0;
    while (s % 2 == 0) {
        s /= 2;
        r++;
    }
    for (size_t i = 0, j; i < sizeof(millerrabin) / sizeof(uint64_t); i++) {
        uint64_t md = mod_pow64(millerrabin[i], s, n);
        if (md != 1) {
            for (j = 1; j < r; j++) {
                if (md == n-1) break;
                md = mod_mult64(md, md, n);
            }
            if (md != n-1) return false;
        }
        if (n < A014233[i]) return true;
    }
    return true;
}
// }}}

vector<uint64_t> candidates;

// Generate all numbers N = product of at least 3 consecutive primes
const uint64_t MAX_VAL = 10'000'000'000'000'000'000ULL;
void init_candidates() {
    for (unsigned start_id = 0; start_id < nprime; ++start_id) {
        uint64_t prod = 1LL;
        for (unsigned end_id = start_id; end_id < nprime; ++end_id) {
            if (prod > MAX_VAL / prime[end_id]) break;
            prod *= prime[end_id];
            candidates.push_back(prod);
        }
    }
    sort(candidates.begin(), candidates.end());
}

uint64_t safe_sqrt(uint64_t n) {
    uint64_t tmp = sqrt(n) + 3;
    while (1ULL * tmp * tmp > n) tmp--;
    return tmp;
}

map<uint64_t, uint64_t> cache_next_prime, cache_prev_prime;

// returns smallest prime >= n
uint64_t next_prime(uint64_t n) {
    if (n <= 2) return 2;

    auto orig = n;
    auto it = cache_next_prime.upper_bound(n);
    if (it != cache_next_prime.begin()) {
        --it;
        if (it->second >= n) {
            return it->second;
        }
    }

    while (n % 6 != 1 && n % 6 != 5) ++n;
    bool stt = n % 6 == 1;
    while (!is_prime(n)) n += stt ? 4 : 2, stt ^= 1;
    return cache_next_prime[orig] = n;
}

uint64_t prev_prime(uint64_t n) {
    assert(n > 1);
    if (n == 2) return 2;
    if (n <= 4) return 3;
    if (n <= 6) return 5;

    auto it = cache_prev_prime.lower_bound(n);
    if (it != cache_prev_prime.end() && it->second <= n) {
        return it->second;
    }
    auto orig = n;

    while (n % 6 != 1 && n % 6 != 5) n--;
    bool stt = n % 6 == 1;
    while (true) {
        if (is_prime(n)) return cache_prev_prime[orig] = n;
        n -= stt ? 2 : 4;
        stt ^= 1;
    }
}

#include <bits/extc++.h>
struct chash { // large odd number for C
    const uint64_t C = uint64_t(4e18 * acos(0)) | 71;
    uint64_t operator()(uint64_t x) const { return __builtin_bswap64(x*C); }
};
__gnu_pbds::gp_hash_table<uint64_t,bool,chash> h({},{},{},{},{1<<16});

bool check(uint64_t x) {
    if (h.find(x) != h.end()) return h[x];

    if (x == 1ULL) return h[x] = false;
    if (is_prime(x)) return h[x] = true;
    // product of 3 consecutive primes
    if (std::binary_search(candidates.begin(), candidates.end(), x)) return h[x] = true;

    auto sq = safe_sqrt(x);
    auto next = next_prime(sq + 1);
    if (x % next) return h[x] = false;
    if (!is_prime(x / next)) return h[x] = false;
    // product of 2 consecutive primes
    return h[x] = (x == next * prev_prime(sq));
}

void solve() {
    sieve();
    init_candidates();
    int ntest; cin >> ntest;
    while (ntest--) {
        uint64_t x; cin >> x;
        cout << (check(x) ? "NICE" : "UGLY") << '\n';
    }
}
