// Solution write up: 
// https://www.facebook.com/code.cung.rr/posts/pfbid034mJrYVsMe8H5bqcPippX5CFkMJkVhxBq85zxX7xoYm76uqZJy62Yy8aTcW7rtDTsl
//
// Idea:
// - 65p: Maintain the distance-time graph (the chart in problem statement).
//   For each gap, we need to maintain all the lines in it - only the 2 endpoints
//   are important
// - 100: Create a data structure that can answer: "Consider 2 scenarios: N-th bus 
//   start at 0 and start at T. What's the difference between the 2 arrival time?"
//   We iterate through sorting stations M-1 -> 0 and update this data structure.
//   We can use the lines in 65p to update the DS.

#include "overtaking.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MAX_SS = 1011;

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

ll op(ll x, ll y) { return max(x, y); }
ll e() { return 0ll; }
ll mapping(ll f, ll s) { return max(s, f); }
ll composition(ll f, ll g) { return max(f, g); }
ll id() { return 0ll; }

// lines[i]: stores lines between i-th and (i+1)-th sorting stations
//           each line is represented by its 2 endpoints
set<pair<ll, ll>> lines[MAX_SS];
int M;
ll X;
vector<int> S;

vector<ll> xs;

using STMax = LazySegTree<ll, op, e, ll, mapping, composition, id>;
STMax st;

void init(
        int L,
        int nBus, vector<ll> T, vector<int> W,
        int _X,
        int _M, vector<int> _S) {
    // subtask 4 {{{
    M = _M;
    X = _X;
    S = _S;

    // sort buses in decreasing order of W (so slowest buses are processed first)
    vector<pair<ll, ll>> buses;
    for (int i = 0; i < nBus; ++i) {
        if (W[i] <= X) continue;
        buses.emplace_back(W[i], T[i]);
    }
    std::sort(buses.begin(), buses.end());
    std::reverse(buses.begin(), buses.end());

    // init gaps between 2 sorting stations
    for (int i = 0; i < M-1; ++i) {  // only M-1 gaps
        lines[i].clear();
        lines[i].insert({0, 0});
    }

    // for each bus, add its line to all gaps
    for (const auto& [w, t] : buses) {
        ll cur_time = t;
        for (int j = 0; j < M-1; ++j) {
            auto it = std::prev(lines[j].lower_bound({cur_time, 0}));
            ll exit_time = std::max(it->second, cur_time + w*(S[j+1] - S[j]));
            lines[j].insert({cur_time, exit_time});

            cur_time = exit_time;
        }
    }
    // }}}

    for (int i = M-2; i >= 0; --i) {
        for (auto [l, r] : lines[i]) {
            if (!l && !r) continue;
            xs.push_back(l - X*S[i] + 1);
            xs.push_back(r - X*S[i+1]);
        }
    }
    std::sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    st = STMax(xs);
    for (int i = M-2; i >= 0; --i) {
        for (auto [l, r] : lines[i]) {
            if (!l && !r) continue;
            int u = lower_bound(xs.begin(), xs.end(), l - X*S[i] + 1) - xs.begin();
            int v = lower_bound(xs.begin(), xs.end(), r - X*S[i+1]) - xs.begin();

            st.apply(u, v+1, st.get(v));
        }
    }
}

ll arrival_time(ll Y) {
    ll tx = X * (ll) S.back();
    if (xs.empty() || Y < xs[0] || Y > xs.back()) return tx + Y;
    return tx + max(Y, st.get(upper_bound(xs.begin(), xs.end(), Y) - xs.begin() - 1));
}
