#include "bits/stdc++.h"
#include "debug.h"
using namespace std;

#define int long long
#define i_1 jakcjacjl
struct Fish {
    int col, row;
    int weight;
};
bool operator < (const Fish& a, const Fish& b) {
    if (a.col != b.col) return a.col < b.col;
    return a.row < b.row;
}

void upMax(int& f, int val) {
    if (val > f) f = val;
}

// sub1 - 3 {{{
// fishes are on even columns -> build piers on odd columns
// & catch all fishes
int sub1(const std::vector<Fish>& fishes) {
    int res = 0;
    for (const auto& fish : fishes) {
        res += fish.weight;
    }
    return res;
}

// fishes are on first 2 columns
int sub2(int n, const std::vector<Fish>& fishes) {
    std::vector<int> zeroes(n);  // prefix sum of fish weights at column == 0
    std::vector<int> ones(n);    // prefix sum of fish weights at column == 1
    for (const auto& fish : fishes) {
        if (fish.col == 0) zeroes[fish.row] += fish.weight;
        if (fish.col == 1) ones[fish.row] += fish.weight;
    }

    std::partial_sum(zeroes.begin(), zeroes.end(), zeroes.begin());
    std::partial_sum(ones.begin(), ones.end(), ones.begin());

    int res = ones.back();  // init: only catch fishes at column == 1
    for (int i = 0; i < n; ++i) {
        // build pier until at column 1, row 0-i
        if (n == 2) upMax(res, zeroes[i]);
        else upMax(res, zeroes[i] + ones.back() - ones[i]);
    }
    return res;
}

// all fishes are on row == 0
int sub3(int n, const std::vector<Fish>& fishes) {
    std::vector<int> weights(n);  // weights[i] = weight of fish at column i
    for (const auto& fish : fishes) {
        weights[fish.col] += fish.weight;
    }

    // f[i] = best strategy if we BUILD PIER AT i, only considering col 0..i
    // i-4 i-3 i-2 i-1 i
    std::vector<int> f(n);
    f[0] = 0;
    for (int i = 1; i < n; ++i) {
        f[i] = std::max(f[i-1], weights[i-1]);
        if (i >= 2) {
            upMax(f[i], f[i-2] + weights[i-1]);
        }
        if (i >= 3) {
            upMax(f[i], f[i-3] + weights[i-2] + weights[i-1]);
        }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        int cur = f[i];
        if (i + 1 < n) cur += weights[i+1];
        upMax(res, cur);
    }
    return res;
}
// }}}

// sub 5 N <= 300 {{{
int sub5(int n, const std::vector<Fish>& fishes) {
    // Init weights[i][j] = sum of fish on column i, from row 0 -> row j
    std::vector<std::vector<int>> weights(n, std::vector<int> (n, 0));
    for (const auto& fish : fishes) {
        weights[fish.col][fish.row] += fish.weight;
    }
    for (int col = 0; col < n; ++col) {
        std::partial_sum(weights[col].begin(), weights[col].end(), weights[col].begin());
    }

    // f[c][r] = best strategy if we last BUILD PIER AT column c, row r
    //           only considering fishes <= (c, r)
    // g[c][r] = similar to f[c][r] but consider fishes at column c, in row [r, n-1]
    std::vector<std::vector<int>> f(n, std::vector<int> (n, 0)),
                                  g(n, std::vector<int> (n, 0));
    // f <= g
    for (int c = 1; c < n; ++c) {
        for (int r = 0; r < n; ++r) {
            // this is first pier
            f[c][r] = g[c][r] = weights[c-1][r];

            // last pier at column i-1
            for (int lastRow = 0; lastRow < n; ++lastRow) {
                if (lastRow <= r) {
                    int cur = std::max(
                            f[c-1][lastRow] + weights[c-1][r] - weights[c-1][lastRow],
                            g[c-1][lastRow]);
                    upMax(f[c][r], cur);
                    upMax(g[c][r], cur);
                } else {
                    upMax(f[c][r], g[c-1][lastRow]);
                    upMax(g[c][r], g[c-1][lastRow] + weights[c][lastRow] - weights[c][r]);
                }
            }

            // last pier at column i-2
            if (c >= 2) {
                for (int lastRow = 0; lastRow < n; ++lastRow) {
                    int cur = g[c-2][lastRow] + weights[c-1][std::max(lastRow, r)];
                    upMax(f[c][r], cur);
                    upMax(g[c][r], cur);
                }
            }
            
            // last pier at column i-3
            if (c >= 3) {
                for (int lastRow = 0; lastRow < n; ++lastRow) {
                    int cur = g[c-3][lastRow] + weights[c-2][lastRow] + weights[c-1][r];
                    upMax(f[c][r], cur);
                    upMax(g[c][r], cur);
                }
            }
        }
    }

    int res = 0;
    for (int c = 0; c < n; ++c) {
        for (int r = 0; r < n; ++r) {
            assert(g[c][r] >= f[c][r]);
            int cur = g[c][r];
            if (c + 1 < n) {
                cur += weights[c+1][r];
            }
            upMax(res, cur);
        }
    }
    return res;
}
// }}}

// SegTree, copied from AtCoder library {{{
// AtCoder doc: https://atcoder.github.io/ac-library/master/document_en/segtree.html
//
// Notes:
// - Index of elements from 0 -> n-1
// - Range queries are [l, r-1]
//
// Tested:
// - (binary search) https://atcoder.jp/contests/practice2/tasks/practice2_j
// - https://oj.vnoi.info/problem/gss
// - https://oj.vnoi.info/problem/nklineup
// - (max_right & min_left for delete position queries) https://oj.vnoi.info/problem/segtree_itstr
// - https://judge.yosupo.jp/problem/point_add_range_sum
// - https://judge.yosupo.jp/problem/point_set_range_composite
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

    int _n, size, log;
    vector<T> d;

    void update(int k) {
        d[k] = op(d[2*k], d[2*k+1]);
    }
};
// }}}

// SegTree examples {{{
// Examples: Commonly used SegTree ops: max / min / sum
struct MaxSegTreeOp {
    static int op(int x, int y) {
        return max(x, y);
    }
    static int e() {
        return INT_MIN;
    }
};

struct MinSegTreeOp {
    static int op(int x, int y) {
        return min(x, y);
    }
    static int e() {
        return INT_MAX;
    }
};

struct SumSegTreeOp {
    static long long op(long long x, long long y) {
        return x + y;
    }
    static long long e() {
        return 0;
    }
};

// Example
// SegTree<int, MaxSegTreeOp::op, MaxSegTreeOp::e> seg_tree(a);
// SegTree<int, MinSegTreeOp::op, MinSegTreeOp::e> seg_tree(a);
// }}}

// AC {{{
int sub7(int n, const std::vector<Fish>& fishes) {
    std::vector<std::vector<int>> rows(n);  // rows[c] = important coordinates at col c
    std::vector<std::vector<int>> weights(n);  // prefix sum of weights
    std::vector<std::vector<std::pair<int,int>>> fishesAt(n);  // stores {row, weight}

    for (const auto& fish : fishes) {
        int c = fish.col;
        rows[c].push_back(fish.row);
        if (c > 0) rows[c-1].push_back(fish.row);
        if (c + 1 < n) rows[c+1].push_back(fish.row);
        fishesAt[c].push_back({fish.row, fish.weight});
    }

    for (int c = 0; c < n; ++c) {
        rows[c].push_back(-1);
        std::sort(rows[c].begin(), rows[c].end());
        rows[c].erase(std::unique(rows[c].begin(), rows[c].end()), rows[c].end());

        std::sort(fishesAt[c].begin(), fishesAt[c].end());

        weights[c].resize(rows[c].size());
        int fish_id = 0;
        for (int i = 0; i < (int) rows[c].size(); ++i) {
            if (i > 0) weights[c][i] = weights[c][i-1];
            while (fish_id < (int) fishesAt[c].size()
                    && fishesAt[c][fish_id].first <= rows[c][i]) {
                weights[c][i] += fishesAt[c][fish_id].second;
                ++fish_id;
            }
        }
    }

    // f[c][r] = best strategy if we last BUILD PIER AT column c, row r
    //           only considering fishes <= (c, r)
    // g[c][r] = similar to f[c][r] but consider fishes at column c, in row [r, n-1]
    std::vector<std::vector<int>> f(n), g(n);
    std::vector<SegTree<int, MaxSegTreeOp::op, MaxSegTreeOp::e>> st_g(n), st_g_with_next_col(n), st_f_with_next_col(n);

    for (int c = 0; c < n; ++c) {
        int sz = static_cast<int> (rows[c].size());
        f[c] = g[c] = std::vector<int> (sz, 0);

        // compute {{{
        if (c > 0) {
            for (int i = 0; i < sz; ++i) {
                int i_1 = std::upper_bound(rows[c-1].begin(), rows[c-1].end(), rows[c][i])
                    - rows[c-1].begin() - 1;

                // this is first pier
                f[c][i] = weights[c-1][i_1];

                // last pier at column i-3
                if (c >= 3) {
                    upMax(f[c][i], st_g_with_next_col[c-3].all_prod() + weights[c-1][i_1]);
                }

                // last pier at column i-2
                if (c >= 2) {
                    upMax(f[c][i], std::max(
                                st_g[c-2].all_prod() + weights[c-1][i_1],
                                st_g_with_next_col[c-2].all_prod()));
                }
                g[c][i] = f[c][i];

                // last pier at column i-1
                if (c >= 1) {
                    // last row <= r
                    int cur = std::max(
                            st_g[c-1].prod(0, i_1+1),
                            st_f_with_next_col[c-1].prod(0, i_1+1) + weights[c-1][i_1]);
                    upMax(f[c][i], cur);
                    upMax(g[c][i], cur);

                    // last row > r
                    upMax(f[c][i], st_g[c-1].prod(i_1+1, (int) g[c-1].size()));
                    upMax(g[c][i], st_g_with_next_col[c-1].prod(i_1+1, (int) g[c-1].size()) - weights[c][i]);
                }
            }
        }
        // }}}

        // aggregate {{{
        st_g[c] = SegTree<int, MaxSegTreeOp::op, MaxSegTreeOp::e> (g[c]);
        if (c + 1 < n) {
            std::vector<int> g_with_next_col(sz), f_with_next_col(sz);
            for (int i = 0; i < sz; ++i) {
                int i_1 = std::upper_bound(rows[c+1].begin(), rows[c+1].end(), rows[c][i])
                    - rows[c+1].begin() - 1;
                g_with_next_col[i] = g[c][i] + weights[c+1][i_1];
                f_with_next_col[i] = f[c][i] - weights[c][i];
            }
            st_g_with_next_col[c] = SegTree<int, MaxSegTreeOp::op, MaxSegTreeOp::e> (g_with_next_col);
            st_f_with_next_col[c] = SegTree<int, MaxSegTreeOp::op, MaxSegTreeOp::e> (f_with_next_col);
        }

        // }}}
    }

    int res = 0;
    for (int c = 0; c < n; ++c) {
        int sz = rows[c].size();
        for (int i = 0; i < sz; ++i) {
            int cur = g[c][i];
            if (c + 1 < n) {
                int i_1 = std::upper_bound(rows[c+1].begin(), rows[c+1].end(), rows[c][i])
                    - rows[c+1].begin() - 1;
                cur += weights[c+1][i_1];
            }
            upMax(res, cur);
        }
    }
    return res;
}
// }}}

#undef int
long long max_weights(
        int n, int nFish,
        std::vector<int> xs,
        std::vector<int> ys,
        std::vector<int> ws) {
    std::vector<Fish> fishes;
    for (int i = 0; i < nFish; ++i) {
        fishes.push_back({xs[i], ys[i], ws[i]});
    }

    if (std::all_of(xs.begin(), xs.end(), [] (int x) { return x % 2 == 0; })) {
        return sub1(fishes);
    }
    if (*std::max_element(xs.begin(), xs.end()) <= 1) {
        return sub2(n, fishes);
    }
    if (*std::max_element(ys.begin(), ys.end()) == 0) {
        return sub3(n, fishes);
    }
    return sub7(n, fishes);
}

int32_t main() {
    int n; std::cin >> n;
    int nFish; std::cin >> nFish;
    std::vector<int> xs(nFish), ys(nFish), ws(nFish);
    for (int i = 0; i < nFish; ++i) {
        std::cin >> xs[i] >> ys[i] >> ws[i];
    }

    DEBUG(max_weights(n, nFish, xs, ys, ws));
}
