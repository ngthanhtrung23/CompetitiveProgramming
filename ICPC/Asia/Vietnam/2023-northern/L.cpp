// template {{{
#include "bits/stdc++.h"
using namespace std;

// #define int long long
#define I(x) int x; cin >> x;
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define FORD(i,a,b) for(int i=(a),_##i##_b=(b); i>=_##i##_b; i--)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))
#define ALL(s) (s).begin(), (s).end()

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)

template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
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
    srand(7777);
    solve();
    return 0;
}

// }}}
// ModInt {{{
template<int MD> struct ModInt {
    using ll = long long;
    int x;

    constexpr ModInt() : x(0) {}
    constexpr ModInt(ll v) { _set(v % MD + MD); }
    constexpr static int mod() { return MD; }
    constexpr explicit operator bool() const { return x != 0; }

    constexpr ModInt operator + (const ModInt& a) const {
        return ModInt()._set((ll) x + a.x);
    }
    constexpr ModInt operator - (const ModInt& a) const {
        return ModInt()._set((ll) x - a.x + MD);
    }
    constexpr ModInt operator * (const ModInt& a) const {
        return ModInt()._set((ll) x * a.x % MD);
    }
    constexpr ModInt operator / (const ModInt& a) const {
        return ModInt()._set((ll) x * a.inv().x % MD);
    }
    constexpr ModInt operator - () const {
        return ModInt()._set(MD - x);
    }

    constexpr ModInt& operator += (const ModInt& a) { return *this = *this + a; }
    constexpr ModInt& operator -= (const ModInt& a) { return *this = *this - a; }
    constexpr ModInt& operator *= (const ModInt& a) { return *this = *this * a; }
    constexpr ModInt& operator /= (const ModInt& a) { return *this = *this / a; }

    friend constexpr ModInt operator + (ll a, const ModInt& b) {
        return ModInt()._set(a % MD + b.x);
    }
    friend constexpr ModInt operator - (ll a, const ModInt& b) {
        return ModInt()._set(a % MD - b.x + MD);
    }
    friend constexpr ModInt operator * (ll a, const ModInt& b) {
        return ModInt()._set(a % MD * b.x % MD);
    }
    friend constexpr ModInt operator / (ll a, const ModInt& b) {
        return ModInt()._set(a % MD * b.inv().x % MD);
    }

    constexpr bool operator == (const ModInt& a) const { return x == a.x; }
    constexpr bool operator != (const ModInt& a) const { return x != a.x; }

    friend std::istream& operator >> (std::istream& is, ModInt& other) {
        ll val; is >> val;
        other = ModInt(val);
        return is;
    }
    constexpr friend std::ostream& operator << (std::ostream& os, const ModInt& other) {
        return os << other.x;
    }

    constexpr ModInt pow(ll k) const {
        ModInt ans = 1, tmp = x;
        while (k) {
            if (k & 1) ans *= tmp;
            tmp *= tmp;
            k >>= 1;
        }
        return ans;
    }

    constexpr ModInt inv() const {
        if (x < 5000111) {
            _precalc(5000111);
            return invs[x];
        }
        int a = x, b = MD, ax = 1, bx = 0;
        while (b) {
            int q = a/b, t = a%b;
            a = b; b = t;
            t = ax - bx*q;
            ax = bx; bx = t;
        }
        assert(a == 1);
        if (ax < 0) ax += MD;
        return ax;
    }

    static std::vector<ModInt> factorials, inv_factorials, invs;
    constexpr static void _precalc(int n) {
        if (factorials.empty()) {
            factorials = {1};
            inv_factorials = {1};
            invs = {0};
        }
        if (n > MD) n = MD;
        int old_sz = factorials.size();
        if (n <= old_sz) return;

        factorials.resize(n);
        inv_factorials.resize(n);
        invs.resize(n);

        for (int i = old_sz; i < n; ++i) factorials[i] = factorials[i-1] * i;
        inv_factorials[n-1] = factorials.back().pow(MD - 2);
        for (int i = n - 2; i >= old_sz; --i) inv_factorials[i] = inv_factorials[i+1] * (i+1);
        for (int i = n-1; i >= old_sz; --i) invs[i] = inv_factorials[i] * factorials[i-1];
    }

    static int get_primitive_root() {
        static int primitive_root = 0;
        if (!primitive_root) {
            primitive_root = [&]() {
                std::set<int> fac;
                int v = MD - 1;
                for (ll i = 2; i * i <= v; i++)
                    while (v % i == 0) fac.insert(i), v /= i;
                if (v > 1) fac.insert(v);
                for (int g = 1; g < MD; g++) {
                    bool ok = true;
                    for (auto i : fac)
                        if (ModInt(g).pow((MD - 1) / i) == 1) {
                            ok = false;
                            break;
                        }
                    if (ok) return g;
                }
                return -1;
            }();
        }
        return primitive_root;
    }

    static ModInt C(int n, int k) {
        _precalc(n + 1);
        return factorials[n] * inv_factorials[k] * inv_factorials[n-k];
    }
    
private:
    // Internal, DO NOT USE.
    // val must be in [0, 2*MD)
    constexpr inline __attribute__((always_inline)) ModInt& _set(ll v) {
        x = v >= MD ? v - MD : v;
        return *this;
    }
};
template <int MD> std::vector<ModInt<MD>> ModInt<MD>::factorials = {1};
template <int MD> std::vector<ModInt<MD>> ModInt<MD>::inv_factorials = {1};
template <int MD> std::vector<ModInt<MD>> ModInt<MD>::invs = {0};
// }}}

const int MN = 5000111;
vector<int> primes;

int smallest_p[MN];  // smallest_p[n] = smallest prime factor of n
void linear_sieve_smallest_prime_factor(int n) {
    primes.clear();
    memset(smallest_p, 0, sizeof smallest_p);

    for (int i = 2; i < n; ++i) {
        if (!smallest_p[i]) primes.push_back(i);
        for (int j = 0; j < int(primes.size()) && i * primes[j] < n; ++j) {
            smallest_p[i * primes[j]] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

const int MOD = 998244353;
using mint = ModInt<MOD>;
using ll = int64_t;

void solve() {
    linear_sieve_smallest_prime_factor(5000011);

    int a, b; cin >> a >> b;
    unordered_set<int> factors_a;
    mint phi_a = a;

    auto add_factor = [&] (int p) {
        factors_a.insert(p);
        phi_a *= mint(1) - mint(p).inv();
    };

    while (a > 1) {
        if (!smallest_p[a]) {
            add_factor(a);
            break;
        } else {
            int p = smallest_p[a];
            while (a % p == 0) a /= p;
            add_factor(p);
        }
    }

    mint sum = 0;
    for (ll mult = 1; mult <= b; ++mult) {
        mint phi = phi_a * mint(a).inv() * mint(a * mult);

        ll u = mult;
        auto add_mult_factor = [&] (int p) {
            if (factors_a.count(p)) return;
            phi *= mint(1) - mint(p).inv();
        };
        while (u > 1) {
            if (!smallest_p[u]) {
                add_mult_factor(u);
                break;
            } else {
                int p = smallest_p[u];
                while (u % p == 0) u /= p;
                add_mult_factor(p);
            }
        }
        sum += phi;
    }
    cout << sum << endl;
}
