// template {{{
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { auto _ = (x); cout << #x << " = "; cout << (_) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(std::begin(declval<Con>()))>
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

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
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
// Usage:
// HashGenerator g(MAX_LENGTH)
//
// auto h = g.hash(s)
// g.equals(s, h, l1, r1, s, h, l2, r2)
// g.cmp(s, h, l1, r1, s, h, l2, r2)
//
// Tested:
// - https://oj.vnoi.info/problem/substr
// - https://oj.vnoi.info/problem/paliny  - max palin / binary search
// - https://oj.vnoi.info/problem/dtksub  - hash<Hash> for unordered_map
// - https://oj.vnoi.info/problem/vostr   - cmp

const int MOD = 1e9 + 7;
using modular = ModInt<MOD>;

struct Hash {
    long long x;
    modular y;

    Hash operator + (const Hash& a) const { return Hash{x + a.x, y + a.y}; }
    Hash operator - (const Hash& a) const { return Hash{x - a.x, y - a.y}; }
    Hash operator * (const Hash& a) const { return Hash{x * a.x, y * a.y}; }
    Hash operator * (int k) const { return Hash{x*k, y*k}; }

    Hash& operator += (const Hash& a) { return *this = *this + a; }
    Hash& operator -= (const Hash& a) { return *this = *this - a; }
    Hash& operator *= (const Hash& a) { return *this = *this * a; }
};
bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}
bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y.x < b.y.x;
}
std::ostream& operator << (std::ostream& out, const Hash& h) {
    out << '(' << h.x << ", " << h.y << ')';
    return out;
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

    template<typename Container>
    std::vector<Hash> hash(const Container& s) const {
        std::vector<Hash> res(s.size());
        for (size_t i = 0; i < s.size(); i++) {
            res[i] = p[i] * (int) s[i];
        }
        std::partial_sum(res.begin(), res.end(), res.begin());
        return res;
    }

    Hash getHash(const std::vector<Hash>& h, int l, int r) const {
        return __getHash(h, l, r) * p[p.size() - 1 - l];
    }

    // compare [l1, r1] vs [l2, r2]
    bool equals(
            const std::vector<Hash>& h1, int l1, int r1,
            const std::vector<Hash>& h2, int l2, int r2) const {
        assert(0 <= l1 && l1 <= r1 && r1 < (int) h1.size());
        assert(0 <= l2 && l2 <= r2 && r2 < (int) h2.size());
        if (r1 - l1 != r2 - l2) return false;

        return getHash(h1, l1, r1) == getHash(h2, l2, r2);
    }

    // Returns length of max common prefix of h1[l1, r1] and h2[l2, r2]
    // length = 0 -> first character of 2 substrings are different.
    int maxCommonPrefix(
            const std::vector<Hash>& h1, int l1, int r1,
            const std::vector<Hash>& h2, int l2, int r2) const {
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
    template<typename Container1, typename Container2>
    int cmp(
            const Container1& s1, const std::vector<Hash>& h1, int l1, int r1,
            const Container2& s2, const std::vector<Hash>& h2, int l2, int r2) const {
        assert(0 <= l1 && l1 <= r1 && r1 < (int) h1.size());
        assert(0 <= l2 && l2 <= r2 && r2 < (int) h2.size());

        int commonPrefixLen = maxCommonPrefix(h1, l1, r1, h2, l2, r2);
        char c1 = (l1 + commonPrefixLen <= r1) ? s1[l1 + commonPrefixLen] : 0;
        char c2 = (l2 + commonPrefixLen <= r2) ? s2[l2 + commonPrefixLen] : 0;

        return (c1 == c2) ? 0 : ((c1 < c2) ? -1 : 1);
    }

    std::vector<Hash> p;

    // DO NOT USE, this doesn't divide by p[l]
    Hash __getHash(const std::vector<Hash>& h, int l, int r) const {
        assert(0 <= l && l <= r && r < (int) h.size());
        return h[r] - (l == 0 ? Hash{0, 0} : h[l-1]);
    }
};
// }}}
// Palindrome Tree {{{
template<int MAXC = 26>
struct PalindromicTree {
    PalindromicTree(const string& str)
            : _sz(str.size() + 5),
              next(_sz, vector<int> (MAXC, 0)),
              link(_sz, 0), qlink(_sz, 0),
              cnt(_sz, 0), right_id(_sz, 0),
              len(_sz, 0), s(_sz, 0) {
        init();
        for (int i = 0; i < (int) str.size(); ++i) {
            add(str[i], i);
        }
        count();
    }
    int _sz;

    // returns vector of (left, right, frequency)
    vector<tuple<int,int,int>> get_palindromes() {
        vector<tuple<int,int,int>> res;
        dfs(0, res);
        dfs(1, res);
        return res;
    }

    void dfs(int u, vector<tuple<int,int,int>>& res) {
        if (u > 1) {  // u = 0 and u = 1 are two empty nodes
            res.emplace_back(right_id[u] - len[u] + 1, right_id[u], cnt[u]);
        }
        for (int i = 0; i < MAXC; ++i) {
            if (next[u][i]) dfs(next[u][i], res);
        }
    }

    int last, n, p;
    vector<vector<int>> next, dlink;
    vector<int> link, qlink, cnt, right_id, len, s;

    int newnode(int l, int right) {
        len[p] = l;
        right_id[p] = right;
        return p++;
    }
    void init() {
        p = 0;
        newnode(0, -1), newnode(-1, -1);
        n = last = 0;
        s[n] = -1, link[0] = 1;
    }
    int getlink(int x) {
        while (s[n - len[x] - 1] != s[n]) {
            if (s[n - len[link[x]] - 1] == s[n]) x = link[x];
            else x = qlink[x];
        }
        return x;
    }
    void add(char c, int right) {
        c -= 'a';
        s[++n] = c;
        int cur = getlink(last);
        if (!next[cur][(int) c]) {
            int now = newnode(len[cur] + 2, right);
            link[now] = next[getlink(link[cur])][(int) c];
            next[cur][(int) c] = now;
            if (s[n - len[link[now]]] == s[n - len[link[link[now]]]]) {
                qlink[now] = qlink[link[now]];
            }
            else {
                qlink[now] = link[link[now]];
            }
        }
        last = next[cur][(int) c];
        cnt[last]++;
    }
    void count() {
        for (int i = p - 1; i >= 0; i--) {
            cnt[link[i]] += cnt[i];
        }
    }
};
// }}}

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;

    // Use `Palindrome Tree` to extract all palindrome substrings
    PalindromicTree tree(s);
    auto palindromes = tree.get_palindromes();

    // Use rolling hash to sort all palindrome substrings
    HashGenerator g(s.size() + 5, 100001);
    auto h = g.hash(s);

    auto cmp_tuples = [&] (const auto& t1, const auto& t2) {
                auto [l1, r1, cnt1] = t1;
                auto [l2, r2, cnt2] = t2;
                return g.cmp(s, h, l1, r1, s, h, l2, r2) < 0;
            };
    sort(palindromes.begin(), palindromes.end(), cmp_tuples);

    vector<int> cnts;
    for (auto [l, r, cnt] : palindromes) {
        cnts.push_back(cnt);
    }
    std::partial_sum(cnts.begin(), cnts.end(), cnts.begin());

    while (q--) {
        int t; cin >> t;
        int id = std::lower_bound(cnts.begin(), cnts.end(), t) - cnts.begin();
        if (id == cnts.size()) { cout << -1 << '\n'; continue; }

        auto [l, r, cnt] = palindromes[id];
        modular sum = h[r].y;
        if (l) sum -= h[l-1].y;
        cout << sum / g.p[l].y << '\n';
    }
}
