// Solution writeup: https://www.facebook.com/code.cung.rr/posts/pfbid02S2q45VzPoxLGUzQvNeiUZRNZdsUvSgLmaYVr87nWMGqDBEwkcB6uAKAb6yBNTxSjl

#include "bits/stdc++.h"
using namespace std;

using Query = std::tuple<int,int,int>;

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

const long long INF = static_cast<long long> (2e18);
struct S { long long suf_min, suf_max; };
S op(S left, S right) {
    return S {
        std::min(left.suf_min, right.suf_min),
        std::max(left.suf_max, right.suf_max),
    };
};
S e() { return S{ INF, -INF }; }
S mapping(long long f, S s) { return S{ f + s.suf_min, f + s.suf_max }; }
long long composition(long long f, long long g) { return f + g; }
long long id() { return 0; }

std::vector<int> sub5(
        const std::vector<int>& c,
        const std::vector<Query>& queries) {
    std::vector< std::vector< std::pair<int, long long> > > addAt(c.size()), removeAt(c.size());
    for (int i = 0; i < (int) queries.size(); ++i) {
        auto [l, r, v] = queries[i];
        addAt[l].push_back({i, v});
        removeAt[r].push_back({i, -v});
    }

    int q = queries.size();
    LazySegTree<S, op, e, long long, mapping, composition, id> st(std::vector<S> (q+1, {0, 0}));
    std::vector<int> a(c.size());
    for (int i = 0; i < (int) a.size(); ++i) {
        for (auto [queryId, val] : addAt[i]) {
            st.apply(queryId + 1, q + 1, val);
        }

        auto suffix_max = [&] (int i) {
            return st.prod(i, q + 1).suf_max;
        };
        auto suffix_min = [&] (int i) {
            return st.prod(i, q + 1).suf_min;
        };
        auto sum_v = [&] (int i) {
            return st.get(i).suf_min;
        };

        // find last index t where suffix_max(t) - suffix_min(t) > c[i]
        auto r = std::views::iota(0, q + 1);
        auto res = std::ranges::partition_point(
                r,
                [&] (int mid) {
                    return suffix_max(mid) - suffix_min(mid) > c[i];
                });

        if (res == r.begin()) a[i] = sum_v(q) - suffix_min(0);
        else {
            --res;
            if (sum_v(*res) < sum_v(q)) {
                // currently touch lower bar, then finally touch upper bar once
                // after touching upper bar:
                // - upper bar will finally be at suffix_max[*res]
                // - final distance to upper bar is suffix_max[*res] - sum_vs
                a[i] = c[i] - (suffix_max(*res) - sum_v(q));
            } else {
                a[i] = sum_v(q) - suffix_min(*res);
            }
        }

        for (auto [queryId, val] : removeAt[i]) {
            st.apply(queryId + 1, q + 1, val);
        }
    }
    return a;
}

std::vector<int> distribute_candies(
        std::vector<int> c,
        std::vector<int> l,
        std::vector<int> r,
        std::vector<int> v) {
    int q = (int) l.size();
    std::vector<Query> queries;
    for (int i = 0; i < q; ++i) {
        queries.push_back({l[i], r[i], v[i]});
    }
    return sub5(c, queries);
}

int main() {
    int n; std::cin >> n;
    std::vector<int> c(n);
    for (int i = 0; i < n; ++i) std::cin >> c[i];

    int q; std::cin >> q;
    std::vector<int> l(q), r(q), v(q);
    for (int i = 0; i < q; ++i) std::cin >> l[i] >> r[i] >> v[i];

    auto res = distribute_candies(c, l, r, v);
    for (int val : res) std::cout << val << ' ';
    std::cout << std::endl;

    return 0;
}
