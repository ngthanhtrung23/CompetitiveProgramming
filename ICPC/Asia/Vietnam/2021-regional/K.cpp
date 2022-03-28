#include "bits/stdc++.h"

using namespace std;

#define int long long

// SegTree
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

// SegTree ops
using S = std::pair<int,int>;  // {cnt, sum}
S op(S left, S right) {
    return {left.first + right.first, left.second + right.second};
}
S e() {
    return {0, 0};
}

enum class QueryType { ADD = 0, QUERY = 1 };

// Query
struct Query {
    QueryType typ;

    int l, r, k;
    int id;
};

int bit[2011][2011];
void update(int u, int v) {
    for (int x = u; x <= 2000; x += x & -x) {
        for (int y = v; y <= 2000; y += y & -y) {
            bit[x][y]++;
        }
    }
}

int get(int u, int v) {
    int res = 0;
    for (int x = u; x > 0; x -= x & -x) {
        for (int y = v; y > 0; y -= y & -y) {
            res += bit[x][y];
        }
    }
    return res;
}

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n; std::cin >> n;
    std::vector<int> a(n); for (int& x : a) cin >> x;

    // compress
    std::vector<int> c = a;
    std::sort(c.begin(), c.end());
    c.erase(std::unique(c.begin(), c.end()), c.end());
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(c.begin(), c.end(), a[i]) - c.begin();
    }

    // compute f[i][j]
    std::vector<std::vector<int>> f(n, std::vector<int> (n, 0));
    for (int i = 0; i < n; i++) {
        SegTree<S, op, e> st(std::vector<S> (c.size(), {0, 0}));

        for (int j = i; j < n; j++) {
            if (i == j) {
                f[i][j] = 0;
            } else {
                auto lower = st.prod(0, a[j]);
                auto higher = st.prod(a[j] + 1, c.size());

                f[i][j] = f[i][j-1]
                    + (c[a[j]] * lower.first - lower.second)
                    + (higher.second - c[a[j]] * higher.first);
            }
            st.set(a[j], op(st.get(a[j]), {1, c[a[j]]}));
        }
    }

    // queries
    int q; std::cin >> q;
    std::vector<int> answers(q);
    std::vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        queries[i].typ = QueryType::QUERY;
        std::cin >> queries[i].l >> queries[i].r >> queries[i].k;
        
        // BIT id from 1
        queries[i].l;
        queries[i].r;
        queries[i].id = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            Query query;
            query.typ = QueryType::ADD;

            // BIT id from 1
            query.l = i + 1;
            query.r = j + 1;
            query.k = f[i][j];
            queries.push_back(query);
        }
    }
    sort(queries.begin(), queries.end(), [&] (const Query& a, const Query& b) {
            if (a.k != b.k) return a.k < b.k;
            return a.typ < b.typ;
            });

    // process queries
    for (const auto& query : queries) {
        if (query.typ == QueryType::ADD) {
            update(query.l, query.r);
        } else {
            answers[query.id] =
                get(2000, query.r) - get(query.l - 1, query.r);
        }
    }

    // answer
    for (int ans : answers) std::cout << ans << '\n';
    return 0;
}
