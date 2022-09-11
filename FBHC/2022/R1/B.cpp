//   sum((x - xi)^2) + sum((y - yi)^2)
// = n*x^2 + sum(xi^2) - 2*x*sum(xi)

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

const int MOD = 1e9 + 7;
using mint = ModInt<MOD>;
void solve() {
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n; cin >> n;
        vector<mint> x(n), y(n);

        mint sumxi_2 = 0, sumxi = 0;
        mint sumyi_2 = 0, sumyi = 0;
        REP(i,n) {
            cin >> x[i] >> y[i];
            sumxi += x[i];
            sumyi += y[i];
            sumxi_2 += x[i] * x[i];
            sumyi_2 += y[i] * y[i];
        }

        int q; cin >> q;
        mint sum = 0;
        while (q--) {
            mint xq, yq; cin >> xq >> yq;
            mint res = mint(n) * (xq*xq + yq*yq);
            res += sumxi_2 + sumyi_2;
            res -= 2*xq*sumxi + 2*yq*sumyi;

            sum += res;
        }
        cout << "Case #" << test << ": " << sum << '\n';
    }
}
