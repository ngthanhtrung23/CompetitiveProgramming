// Solution write up: https://www.facebook.com/code.cung.rr/posts/pfbid0xAN3LbWb4hhtvzzpEJRLcGJJdthkuWWUdBU8VWHB5pBR1nEx1DRFT3q8xXHjPt5Cl
#include "sequence.h"
#include <bits/stdc++.h>
#define SZ(s) ((int) ((s).size()))
using namespace std;
 
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
// SegTree examples {{{
// Examples: Commonly used SegTree ops: max / min / sum
using S = pair<int,int>;
S op(S left, S right) {
    return {
        min(left.first, right.first),
        max(left.second, right.second),
    };
}
S e() {
    return {
        1000111000,
        -1000111000,
    };
}
 
using F = int;
S mapping(F f, S s) {
    return {
        s.first + f,
        s.second + f,
    };
}
F composition(F f, F g) {
    return f + g;
}
F id() { return 0; }
 
// using STMax = SegTree<int, MaxSegTreeOp::op, MaxSegTreeOp::e>;
// using STMin = SegTree<int, MinSegTreeOp::op, MinSegTreeOp::e>;
// }}}
 
vector<int> cached_geq_right, cached_geq_left, cached_g_right, cached_g_left;
void initCache(int n, const vector<int>& a, const vector<vector<int>>& ids) {
    cached_geq_right.resize(n + 1);
    cached_geq_left.resize(n + 1);
    cached_g_right.resize(n + 1);
    cached_g_left.resize(n + 1);
    LazySegTree<S, op, e, F, mapping, composition, id> st_geq(n + 1), st_g(n + 1);
    // st_geq: >= median: +1; < median: -1
    // st_g: > median: +1; <= median: -1
    st_geq.set(0, {0, 0});
    st_g.set(0, {0, 0});
 
    for (int median = 0; median <= n; ++median) {
        if (median == 0) {
            for (int i = 1; i <= n; ++i) {
                st_geq.set(i, {i, i});
                st_g.set(i, {i, i});
            }
        } else {
            for (int i : ids[median]) {
                st_g.apply(i, n+1, -2);
            }
            for (int i : ids[median-1]) {
                st_geq.apply(i, n+1, -2);
            }
        }
        for (int i : ids[median]) {
            cached_geq_right[i] = st_geq.prod(i, n+1).second;
            cached_geq_left[i] = st_geq.prod(0, i).first;
 
            cached_g_right[i] = st_g.prod(i, n+1).first;
            cached_g_left[i] = st_g.prod(0, i).second;
        }
    }
}
 
bool can(int n, int eq, const vector<int>& a, const vector<vector<int>>& ids) {
    for (int median = 0; median <= n; median++) {
        if (SZ(ids[median]) < eq) continue;
        for (int ix = 0, iy = eq-1; iy < SZ(ids[median]); ++ix, ++iy) {
            int x = ids[median][ix];
            int y = ids[median][iy];
 
            // find [l, r]:
            // - l <= x < y <= r
            // - less + eq >= greater
            // - greater + eq >= less
            // - eq >= greater - less >= -eq
            // - eq >= (greater(r) - less(r)) - (greater(l-1) - less(l-1)) >= -eq
 
            int max_val = cached_geq_right[y] - cached_geq_left[x];
            int min_val = cached_g_right[y] - cached_g_left[x];
            if (max_val * (int64_t) min_val <= 0) return true;
        }
    }
    return false;
}
int sequence(int n, std::vector<int> a) {
    // ids from 1
    a.insert(a.begin(), 0);
 
    vector<vector<int>> ids(n + 1);
    for (int i = 1; i <= n; ++i) {
        ids[a[i]].push_back(i);
    }
    initCache(n, a, ids);
 
    int left = 1, right = n, res = 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (can(n, mid, a, ids)) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return res;
}
