#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
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
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_rand(long long r) {
    return uniform_int_distribution<long long> (0, r-1)(rng);
}

template<typename T>
vector<T> read_vector(int n) {
    vector<T> res(n);
    for (int& x : res) cin >> x;
    return res;
}

void solve();

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}

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

    friend std::istream& operator >> (std::istream& is, ModInt& x) {
        ll val; is >> val;
        x = ModInt(val);
        return is;
    }
    constexpr friend std::ostream& operator << (std::ostream& os, const ModInt& x) {
        return os << x.x;
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
        if (x < 1000111) {
            _precalc(1000111);
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

// Hash {{{
const int MOD = 1e9 + 7;
using modular = ModInt<MOD>;

struct Hash {
    long long x;
    modular y;

    Hash operator + (const Hash& a) const { return Hash{x + a.x, y + a.y}; }
    Hash operator - (const Hash& a) const { return Hash{x - a.x, y - a.y}; }
    Hash operator * (const Hash& a) const { return Hash{x * a.x, y * a.y}; }
    Hash operator * (int k) const { return Hash{x*k, y*k}; }
};
bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}

// hash function for std::unordered_map
namespace std {
    template<>
    struct hash<Hash> {
        public:
            size_t operator() (const Hash& h) const {
                return h.x * 1000000009 + h.y.x;
            }
    };
}

struct HashGenerator {
    HashGenerator(int maxLen, int base = 311) {
        p.resize(maxLen + 1);
        p[0] = {1, 1};
        for (int i = 1; i <= maxLen; i++) {
            p[i] = p[i-1] * base;
        }
    }

    std::vector<Hash> hash(const std::vector<int>& s) {
        std::vector<Hash> res(s.size());
        for (size_t i = 0; i < s.size(); i++) {
            res[i] = p[i] * (int) s[i];
        }
        std::partial_sum(res.begin(), res.end(), res.begin());
        return res;
    }

    Hash getHash(const std::vector<Hash>& h, int l, int r) {
        return __getHash(h, l, r) * p[p.size() - 1 - l];
    }

    // compare [l1, r1] vs [l2, r2]
    bool equals(
            const std::vector<Hash>& h1, int l1, int r1,
            const std::vector<Hash>& h2, int l2, int r2) {
        assert(0 <= l1 && l1 <= r1 && r1 < (int) h1.size());
        assert(0 <= l2 && l2 <= r2 && r2 < (int) h2.size());
        if (r1 - l1 != r2 - l2) return false;

        return getHash(h1, l1, r1) == getHash(h2, l2, r2);
    }

    // Returns length of max common prefix of h1[l1, r1] and h2[l2, r2]
    // length = 0 -> first character of 2 substrings are different.
    int maxCommonPrefix(
            const std::vector<Hash>& h1, int l1, int r1,
            const std::vector<Hash>& h2, int l2, int r2) {
        assert(0 <= l1 && l1 <= r1 && r1 < (int) h1.size());
        assert(0 <= l2 && l2 <= r2 && r2 < (int) h2.size());

        int len1 = r1 - l1 + 1;
        int len2 = r2 - l2 + 1;

        int res = -1, left = 0, right = std::min(len1, len2) - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (equals(h1, l1, l1 + mid, h2, l2, l2 + mid)) {
                res = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return res + 1;
        /* C++20
        auto r = std::views::iota(0, std::min(len1, len2));
        auto res = std::ranges::partition_point(
                r,
                [&] (int mid) {
                    return equals(h1, l1, l1+mid, h2, l2, l2+mid);
                });
        return *res;
         */
    }

    // compare s1[l1, r1] and s2[l2, r2]
    int cmp(
            const std::vector<int>& s1, const std::vector<Hash>& h1, int l1, int r1,
            const std::vector<int>& s2, const std::vector<Hash>& h2, int l2, int r2) {
        assert(0 <= l1 && l1 <= r1 && r1 < (int) h1.size());
        assert(0 <= l2 && l2 <= r2 && r2 < (int) h2.size());

        int commonPrefixLen = maxCommonPrefix(h1, l1, r1, h2, l2, r2);
        char c1 = (l1 + commonPrefixLen <= r1) ? s1[l1 + commonPrefixLen] : 0;
        char c2 = (l2 + commonPrefixLen <= r2) ? s2[l2 + commonPrefixLen] : 0;

        return (c1 == c2) ? 0 : ((c1 < c2) ? -1 : 1);
    }

private:
    std::vector<Hash> p;

    // DO NOT USE, this doesn't divide by p[l]
    Hash __getHash(const std::vector<Hash>& h, int l, int r) {
        assert(0 <= l && l <= r && r < (int) h.size());
        return h[r] - (l == 0 ? Hash{0, 0} : h[l-1]);
    }
};
// }}}

bool can(int n, int k, vector<int> a, vector<int> b) {
    assert(n > 1);

    if (n == 2) {
        if (k % 2 == 1) swap(a[0], a[1]);
        return a == b;
    }
    if (k == 0) {
        return a == b;
    }

    HashGenerator g(n, 500009);
    auto ha = g.hash(a);
    auto hb = g.hash(b);

    if (a == b) {
        if (k != 1) return true;
    }

    FOR(i,1,n-1) {
        // a[i..n-1] == b[0..n-i-1]
        // a[0..i-1] == b[n-i..n-1]

        if (g.equals(ha, i, n-1, hb, 0, n-i-1)
                && g.equals(ha, 0, i-1, hb, n-i, n-1)) {
            return true;
        }
    }
    return false;
}

void solve() {
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n, k; cin >> n >> k;

        vector<int> a(n), b(n);
        for(int& x : a) cin >> x;
        for(int& x : b) cin >> x;

        cout << "Case #" << test << ": " << (can(n, k, a, b) ? "YES" : "NO") << endl;
    }
}

// 5 1 2 4 3 --> 5 1 2 3 4

// 1 2 4 3   5
// 2 4 3   5 1
// 4 3   5 1 2
// 3   5 1 2 4
