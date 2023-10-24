// template {{{
#include "bits/stdc++.h"
using namespace std;

#define int long long
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
// Compressor {{{
/* Example usage:
    auto compressor = CompressorBuilder<T>{vs}.build();
    int x = compessor.must_eq(vs[0]);
    compressor.compress_inplace(vs);
*/
// Based on https://suisen-cp.github.io/cp-library-cpp/library/util/coordinate_compressor.hpp
template<typename T>
struct CompressorBuilder {
    // Do not use directly. Use builder.build()
    struct Compressor {
        // Number of unique keys
        int size() const { return xs.size(); }

        void compress_inplace(std::vector<T>& vals) {
            for (int& val : vals) {
                val = must_eq(val);
            }
        }

        [[nodiscard]] std::vector<T> compress(const std::vector<T>& vals) {
            std::vector<T> res(vals.size());
            for (int i = 0; i < static_cast<int> (res.size()); ++i) {
                res[i] = must_eq(vals[i]);
            }
            return res;
        }

        bool has_key(const T& key) const {
            return std::binary_search(xs.begin(), xs.end(), key);
        }

#define LB(key) std::lower_bound(xs.begin(), xs.end(), key)
#define UB(key) std::upper_bound(xs.begin(), xs.end(), key)

        // throw exception if no such key is found
        int must_eq(const T& key) {
            auto it = LB(key);
            assert(it != xs.end());
            return it - xs.begin();
        }
        // throw exception if no such key is found
        int must_geq(const T& key) {
            auto it = LB(key);
            assert(it != xs.end());
            return it - xs.begin();
        }
        // throw exception if no such key is found
        int must_gt(const T& key) {
            auto it = UB(key);
            assert(it != xs.end());
            return it - xs.begin();
        }
        // throw exception if no such key is found
        int must_leq(const T& key) {
            auto it = UB(key);
            assert(it != xs.begin());
            return it - xs.begin() - 1;
        }
        // throw exception if no such key is found
        int must_lt(const T& key) {
            auto it = LB(key);
            assert(it != xs.begin());
            return it - xs.begin() - 1;
        }
#undef LB
#undef UB

        std::vector<T> xs;
    };

    auto build() {
        std::sort(xs.begin(), xs.end());
        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
        return Compressor{xs};
    }

    void add(const T& key) { xs.push_back(key); }
    void add(T&& key) { xs.push_back(std::move(key)); }

    std::vector<T> xs;
};
// }}}
// 1D Fenwick {{{
// 0 based index
//
// Tested:
// - https://judge.yosupo.jp/problem/static_range_sum
// - https://judge.yosupo.jp/problem/point_add_range_sum
template<
    typename T  // need to support operators + -
> struct Fenwick {
    Fenwick(int _n) : n(_n), f(_n + 1) {}

    // a[u] += val
    void update(int u, T val) {
        assert(0 <= u && u < n);
        ++u;
        for (; u <= n; u += u & -u) {
            f[u] += val;
        }
    }

    // return a[0] + .. + a[u-1]
    T get(int u) const {
        assert(0 <= u && u <= n);
        T res = 0;
        for (; u > 0; u -= u & -u) {
            res += f[u];
        }
        return res;
    }

    // return a[l] + .. + a[r-1]
    T get(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return 0;  // empty
        return get(r) - get(l);
    }

    void reset() {
        std::fill(f.begin(), f.end(), T(0));
    }

    int n;
    vector<T> f;
};
// }}}

template<typename T>
long long count_inversions(vector<T> vs) {
    int n = vs.size();
    auto compressor = CompressorBuilder<T>{vs}.build();
    compressor.compress_inplace(vs);
    Fenwick<int> bit(n);

    long long res = 0;
    for (auto v : vs) {
        res += bit.get(v+1, n);
        bit.update(v, +1);
    }
    return res;
}

void solve_one_test() {
    int na, nb; cin >> na >> nb;
    vector<int> a(na), b(nb);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;
    sort(b.begin(), b.end());

    // p[i] = we insert b[i] before p[i]-th position in array a
    vector<int> p(nb);
    // We need to insert b[lb..rb] into positions p[lb], p[lb+1], ..., p[rb]
    // where la <= p[lb] <= p[lb+1] <= ... <= p[rb] <= ra
    function<void(int, int, int, int)> go = [&](int lb, int rb, int la, int ra) {
        if (lb > rb) return;
        int mid = (lb + rb) / 2;
        int smaller_after = 0, greater_before = 0;
        for (int i = la; i < ra; ++i) smaller_after += a[i] < b[mid];

        pair<int,int> best = {smaller_after, la};
        for (int i = la; i <= ra; ++i) {
            best = min(best, {smaller_after + greater_before, i});
            if (a[i] < b[mid]) --smaller_after;
            if (a[i] > b[mid]) ++greater_before;
        }
        p[mid] = best.second;
        go(lb, mid - 1, la, p[mid]);
        go(mid+1, rb, p[mid], ra);
    };
    go(0, nb-1, 0, na);

    vector<int> ab;
    int last_a = -1;
    for (int i = 0; i < nb; ++i) {
        while (last_a + 1 < p[i]) {
            ab.push_back(a[++last_a]);
        }
        ab.push_back(b[i]);
    }
    while (last_a + 1 < na) {
        ab.push_back(a[++last_a]);
    }
    cout << count_inversions(ab) << endl;
}

void solve() {
    int ntest; cin >> ntest;
    while (ntest--) solve_one_test();
}
