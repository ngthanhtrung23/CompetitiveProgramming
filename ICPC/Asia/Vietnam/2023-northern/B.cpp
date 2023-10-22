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
// Lazy Segment Tree, copied from AtCoder {{{
// Source: https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp
// Doc: https://atcoder.github.io/ac-library/master/document_en/lazysegtree.html
//
// Notes:
// - Index of elements from 0
// - Range queries are [l, r-1]
// - composition(f, g) should return f(g())
//
// Tested:
// - https://oj.vnoi.info/problem/qmax2
// - https://oj.vnoi.info/problem/lites
// - (range set, add, mult, sum) https://oj.vnoi.info/problem/segtree_itmix
// - (range add (i-L)*A + B, sum) https://oj.vnoi.info/problem/segtree_itladder
// - https://atcoder.jp/contests/practice2/tasks/practice2_l
// - https://judge.yosupo.jp/problem/range_affine_range_sum

int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}
template<
    class S,                 // node data type
    S (*op) (S, S),          // combine 2 nodes
    S (*e) (),               // identity element
    class F,                 // lazy propagation tag
    S (*mapping) (F, S),     // apply tag F on a node
    F (*composition) (F, F), // combine 2 tags
    F (*id)()                // identity tag
>
struct LazySegTree {
    LazySegTree() : LazySegTree(0) {}
    explicit LazySegTree(int n) : LazySegTree(vector<S>(n, e())) {}
    explicit LazySegTree(const vector<S>& v) : _n((int) v.size()) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    // 0 <= p < n
    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // 0 <= p < n
    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    // Get product in range [l, r-1]
    // 0 <= l <= r <= n
    // For empty segment (l == r) -> return e()
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() {
        return d[1];
    }

    // 0 <= p < n
    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // Apply f on all elements in range [l, r-1]
    // 0 <= l <= r <= n
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    // Binary search on SegTree to find largest r:
    //    f(op(a[l] .. a[r-1])) = true   (assuming empty array is always true)
    //    f(op(a[l] .. a[r])) = false    (assuming op(..., a[n]), which is out of bound, is always false)
    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    // Binary search on SegTree to find smallest l:
    //    f(op(a[l] .. a[r-1])) = true      (assuming empty array is always true)
    //    f(op(a[l-1] .. a[r-1])) = false   (assuming op(a[-1], ..), which is out of bound, is always false)
    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }


private:
    int _n, size, log;
    vector<S> d;
    vector<F> lz;

    void update(int k) {
        d[k] = op(d[2*k], d[2*k+1]);
    }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2*k, lz[k]);
        all_apply(2*k+1, lz[k]);
        lz[k] = id();
    }
};
// }}}
// Area of union of rectangles {{{
namespace area_of_union_of_rectangles {
    using ll = long long;
    const int INF = std::numeric_limits<int>::max() / 2;

    struct Rect {
        int x1, y1, x2, y2;
    };
    istream& operator >> (istream& cin, Rect& r) {
        cin >> r.x1 >> r.y1 >> r.x2 >> r.y2;
        return cin;
    }
    ostream& operator << (ostream& cout, const Rect& r) {
        cout << r.x1 << ' ' << r.y1 << ' ' << r.x2 << ' ' << r.y2;
        return cout;
    }

    struct S {
        int min_cnt;
        ll sum;
    };
    S op(S x, S y) {
        if (x.min_cnt < y.min_cnt) return x;
        if (y.min_cnt < x.min_cnt) return y;
        return { x.min_cnt, x.sum + y.sum };
    }
    S e() { return { INF, 0 }; }
    S mapping(int f, S s) { return { s.min_cnt + f, s.sum }; }
    int composition(int f, int g) { return f + g; }
    int id() { return 0; }
    using ST = LazySegTree<S, op, e, int, mapping, composition, id>;

    ll solve(const std::vector<Rect>& rects) {
        if (rects.empty()) return ll(0);

        const int n = rects.size();
        std::vector<std::tuple<int, int, int, int>> events; events.reserve(2*n);
        std::vector<int> ys; ys.reserve(2*n);

        for (const auto& r : rects) {
            events.emplace_back(r.x1, r.y1, r.y2, +1);
            events.emplace_back(r.x2, r.y1, r.y2, -1);
            ys.push_back(r.y1);
            ys.push_back(r.y2);
        }
        std::sort(events.begin(), events.end(), [] (const auto& e1, const auto& e2) {
                return std::get<0>(e1) < std::get<0>(e2); });
        std::sort(ys.begin(), ys.end());
        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

        const int nys = ys.size();
        std::vector<S> init(nys - 1);
        for (int i = 0; i < nys - 1; ++i) {
            init[i] = { 0, ys[i+1] - ys[i] };
        }
        ST st(init);

        ll res = 0;
        ll lx = std::get<0>(events.front());  // events[i-1].x
        for (int i = 0; lx != std::get<0>(events.back());) {
            for (;; ++i) {
                auto [xi, d, u, add] = events[i];
                if (xi != lx) break;
                int ly = std::lower_bound(ys.begin(), ys.end(), d) - ys.begin();
                int ry = std::lower_bound(ys.begin(), ys.end(), u) - ys.begin();
                st.apply(ly, ry, add);
            }
            ll rx = std::get<0> (events[i]);
            auto [min_cnt, sum] = st.all_prod();
            res += (rx - lx) * (ys.back() - ys.front() - (min_cnt == 0 ? sum : ll(0)));
            lx = rx;
        }
        return res;
    }
}
// }}}

using namespace area_of_union_of_rectangles;

void solve() {
    int x1 = 0, y1 = 0;
    int k; cin >> k;
    int n; cin >> n;
    vector<Rect> rects;
    for (int i = 0; i < n; ++i) {
        char dir; cin >> dir;
        int dist; cin >> dist;

        int new_x1 = x1, new_y1 = y1;
        if (dir == 'E') new_x1 += dist;
        else if (dir == 'W') new_x1 -= dist;
        else if (dir == 'N') new_y1 += dist;
        else if (dir == 'S') new_y1 -= dist;
        else cout << ":@)" << endl;

        rects.push_back({
                min(x1, new_x1), min(y1, new_y1),
                max(x1, new_x1) + k, max(y1, new_y1) + k});

        x1 = new_x1; y1 = new_y1;
    }
    cout << area_of_union_of_rectangles::solve(rects) << endl;
}
