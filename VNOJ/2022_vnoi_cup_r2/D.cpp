#include "bits/stdc++.h"
using namespace std;

int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

template<
    class T,  // data type for nodes
    T (*op) (T, T),  // operator to combine 2 nodes
    T (*e)() // identity element
>
struct SegTree {
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<T> (n, e())) {}
    explicit SegTree(const vector<T>& v) : _n((int) v.size()) {
        log = ceil_pow2(_n);
        size = 1<<log;
        d = vector<T> (2*size, e());

        for (int i = 0; i < _n; i++) d[size+i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    // 0 <= p < n
    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // 0 <= p < n
    T get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    // Get product in range [l, r-1]
    // 0 <= l <= r <= n
    // For empty segment (l == r) -> return e()
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        T sml = e(), smr = e();
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    T all_prod() const {
        return d[1];
    }

    // Binary search on SegTree to find largest r:
    //    f(op(a[l] .. a[r-1])) = true   (assuming empty array is always true)
    //    f(op(a[l] .. a[r])) = false    (assuming op(..., a[n]), which is out of bound, is always false)
    template <bool (*f)(T)> int max_right(int l) const {
        return max_right(l, [](T x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        T sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
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
    template <bool (*f)(T)> int min_left(int r) const {
        return min_left(r, [](T x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        T sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
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
    vector<T> d;

    void update(int k) {
        d[k] = op(d[2*k], d[2*k+1]);
    }
};

// Examples: Commonly used SegTree ops: max / min / sum
struct MaxSegTreeOp {
    static pair<int,int> op(pair<int,int> x, pair<int,int> y) {
        return max(x, y);
    }
    static pair<int,int> e() {
        return {INT_MIN, -1};
    }
};

struct MinSegTreeOp {
    static pair<int,int> op(pair<int,int> x, pair<int,int> y) {
        return min(x, y);
    }
    static pair<int,int> e() {
        return {INT_MAX, -1};
    }
};

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n, k; std::cin >> n >> k;
    std::vector<int> colors(n);
    // id_of[color] = list of x where colors[x] == color
    std::vector<std::vector<int>> id_of(n + 1);
    std::vector<int> pos_in_id_of(n);
    for (int i = 0; i < n; i++) {
        std::cin >> colors[i];
        pos_in_id_of[i] = id_of[colors[i]].size();
        id_of[colors[i]].push_back(i);
    }

    for (int c = 0; c <= n; c++) {
        for (int t = 0; t < k + 1; t++) {
            id_of[c].push_back(n);
        }
    }

    // read queries
    int q; std::cin >> q;
    std::vector< std::pair<int,int> > queries(q);

    // queriesAt[i] contain ids of all queries with i == query.l
    std::vector< std::vector<int> > queriesAt(n);
    for (int i = 0; i < q; i++) {
        auto& [l, r] = queries[i];
        std::cin >> l >> r;
        --l; --r;
        queriesAt[l].push_back(i);
    }

    // answer offline
    std::vector<int> res(q);
    // SegTree contains {value, id}
    SegTree<pair<int,int>, MaxSegTreeOp::op, MaxSegTreeOp::e> min_r(n);
    SegTree<pair<int,int>, MinSegTreeOp::op, MinSegTreeOp::e> max_r(n);

    for (int i = n-1; i >= 0; i--) {
        int color = colors[i];
        auto id = pos_in_id_of[i];

        // remove next appearance of colors[i]
        int j = id_of[color][id + 1];
        if (j < n) {
            min_r.set(j, {0, j});
            max_r.set(j, {n, j});
        }
        // update [min_r, max_r] according to colors[i]
        min_r.set(i, {id_of[color][id + k - 1], i});
        max_r.set(i, {id_of[color][id + k] - 1, i});

        // answer all queries with query.l == i
        for (auto qid : queriesAt[i]) {
            auto [l, r] = queries[qid];

            auto [cur_min_r, id1] = min_r.prod(l, r + 1);
            if (cur_min_r > r) {
                res[qid] = colors[id1];
            }
            auto [cur_max_r, id2] = max_r.prod(l, r + 1);
            if (cur_max_r < r) {
                res[qid] = colors[id2];
            }
        }
    }

    for (auto r : res) {
        std::cout << r << '\n';
    }
    return 0;
}
