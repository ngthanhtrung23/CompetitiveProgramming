// template {{{
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define SZ(s) ((int) ((s).size()))
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
long long get_rand(long long l, long long r) {
    return uniform_int_distribution<long long> (l, r)(rng);
}

void solve();

template<typename T> void upMin(T& x, T val) { if (val < x) x = val; }
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}

// }}}
// RMQ {{{
//
// Sparse table
// Usage:
// RMQ<int, _min> st(v);
//
// Note:
// - doesn't work for empty range
//
// Tested:
// - https://judge.yosupo.jp/problem/staticrmq
template<class T, T (*op) (T, T)> struct RMQ {
    RMQ() = default;
    RMQ(const vector<T>& v) : t{v}, n{(int) v.size()} {
        for (int k = 1; (1<<k) <= n; ++k) {
            t.emplace_back(n - (1<<k) + 1);
            for (int i = 0; i + (1<<k) <= n; ++i) {
                t[k][i] = op(t[k-1][i], t[k-1][i + (1<<(k-1))]);
            }
        }
    }

    // get range [l, r-1]
    // doesn't work for empty range
    T get(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        int k = __lg(r - l);
        return op(t[k][l], t[k][r - (1<<k)]);
    }

private:
    vector<vector<T>> t;
    int n;
};
template<class T> T _min(T a, T b) { return b < a ? b : a; }
template<class T> T _max(T a, T b) { return a < b ? b : a; }
// }}}
// Buffered reader {{{
namespace IO {
    const int BUFSIZE = 1<<14;
    char buf[BUFSIZE + 1], *inp = buf;

    bool reacheof;
    char get_char() {
        if (!*inp && !reacheof) {
            memset(buf, 0, sizeof buf);
            int tmp = fread(buf, 1, BUFSIZE, stdin);
            if (tmp != BUFSIZE) reacheof = true;
            inp = buf;
        }
        return *inp++;
    }
    template<typename T>
    T get() {
        int neg = 0;
        T res = 0;
        char c = get_char();
        while (!std::isdigit(c) && c != '-' && c != '+') c = get_char();
        if (c == '+') { neg = 0; }
        else if (c == '-') { neg = 1; }
        else res = c - '0';

        c = get_char();
        while (std::isdigit(c)) {
            res = res * 10 + (c - '0');
            c = get_char();
        }
        return neg ? -res : res;
    }
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

void solve() {
    int n = IO::get<int>();
    int nQuery = IO::get<int>();
    vector<int> a(n); for (int& x : a) x = IO::get<int>();
    vector<long long> res(nQuery);

    // initialize queries {{{
    vector<tuple<int,int,int,int>> queries(nQuery);
    for (int i = 0; i < nQuery; ++i) {
        auto& [d, l, r, id] = queries[i];
        l = IO::get<int>() - 1;
        r = IO::get<int>() - 1;
        d = IO::get<int>();
        id = i;
    }
    sort(queries.begin(), queries.end());
    // }}}
    // initialize updates {{{
    RMQ<int, __gcd> rmq(a);
    vector<tuple<int, int,int,int>> updates;

    auto findLastSameGcd = [&] (int i, int searchFrom, int d) {
        int res = searchFrom;
        int l = searchFrom + 1, r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (rmq.get(i, mid + 1) == d) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return res;
    };

    for (int i = 0; i < n; ++i) {
        int d = a[i];
        int left = i;  // gcd(a[i], ..., a[left]) == d
        while (left < n) {
            int right = findLastSameGcd(i, left, d);
            // cout << i << ": " << left << " -> " << right << "  " << d << endl;
            updates.push_back({d, i, left, right});

            left = right + 1;
            if (left < n) {
                d = rmq.get(i, left + 1);
            }
        }
    }
    sort(updates.begin(), updates.end());
    // }}}

    // Updates: for each i and d, computes left(i, d) and right(i, d) such that:
    //   GCD(a[i]..a[j]) == d for all j in [left(i, d), right(i, d)]
    //
    // -> when d increases and fixed i, left(i, d) increases
    //
    // Consider all updates processed so far, let d0 = current value of d
    // -> last[i] = left(i, d0)
    // -> last[i] always decreases
    vector<int> last(n, n);
    Fenwick<long long> fenwick(n+1);

    int curUpdate = 0;
    for (const auto& [d, u, v, qid] : queries) {
        // Update:
        // - add point (i, last[i])
        while (curUpdate < SZ(updates) && std::get<0> (updates[curUpdate]) <= d) {
            const auto& [_, i, left, right] = updates[curUpdate++];
            if (last[i] < n) {
                fenwick.update(i, -last[i]);
            }
            last[i] = left;
            fenwick.update(i, last[i]);
        }

        // Query:
        // - result = (sum
        //
        // last[i] is increasing, e.g. [0, 2, 3, 3, 6, 6]
        // --> there's some range [u, furthest] where all last[i] <= v, i in [u, furthest]
        //   & we can binary search to find furthest
        int furthest = u - 1;
        int l = u, r = v;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (last[mid] <= v) {
                furthest = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        res[qid] = (v + 1LL) * (furthest - u + 1) - fenwick.get(u, furthest + 1);
    }

    for (auto r : res) cout << r << '\n';
}
