// template {{{
// CF pragma: https://codeforces.com/blog/entry/96344
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#ifndef UNSAFE_NO_DEFINE_INT_LONG_LONG
#endif
#define I(x) int x; cin >> x;
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define FORD(i,a,b) for(int i=(a),_##i##_b=(b); i>=_##i##_b; i--)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)
#define ALL(s) s.begin(), s.end()

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
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if (i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
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

// Input for pair and vector
template<class U, class V> istream& operator >> (istream& in, pair<U, V>& p) {
    return in >> p.first >> p.second;
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, istream&>::type
operator >> (istream& in, Con& con) {
    for (auto& elem : con) in >> elem;
    return in;
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
    for (auto& x : res) cin >> x;
    return res;
}

void solve();

template<typename T> void upMin(T& x, T val) { if (val < x) x = val; }
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}

template<typename T>
class Set : public std::multiset<T> {
private:
    size_t erase(const T& key) {
        return std::multiset<T>::erase(key);
    }
public:
    using std::multiset<T>::multiset;
    using std::multiset<T>::insert;
    using std::multiset<T>::erase;
};
template<typename T>
class UniqueSet : public std::set<T> {
    using std::set<T>::set;
};
#define set do_not_use_set
// }}}
// Container operations, idea from https://codeforces.com/submissions/Yuu {{{
template<typename T> struct accumulator_type { using type = T; };
template<> struct accumulator_type<int32_t> { using type = int64_t; };
template<> struct accumulator_type<uint32_t> { using type = uint64_t; };
template<> struct accumulator_type<int64_t> { using type = __int128_t; };
template<> struct accumulator_type<uint64_t> { using type = __uint128_t; };

enum ReduceOp { MIN, MAX };
template<typename Container>
auto operator | (const Container& a, ReduceOp op) {
    switch (op) {
        case MIN:
            return *min_element(a.begin(), a.end());
        case MAX:
            return *max_element(a.begin(), a.end());
    }
    assert(false);
}
enum SumOp { SUM, SUM_XOR };
template<typename Container>
auto operator | (const Container& a, SumOp op) {
    typename accumulator_type<typename Container::value_type>::type sum{};
    switch (op) {
        case SUM:
            for (const auto& elem : a) sum += elem;
            return sum;
        case SUM_XOR:
            for (const auto& elem : a) sum ^= elem;
            return sum;
    }
    assert(false);
}
enum ComparableOp { SORT };
template<typename Container>
Container& operator | (Container& a, ComparableOp op) {
    __typeof(a) values;
    switch (op) {
        case SORT:
            std::sort(a.begin(), a.end());
            break;
    }
    return a;
}
enum TransformOp { ADD_1, PREFIX_SUM, PREFIX_SUM_XOR, REVERSE, SUB_1, COMPRESS };
template<typename Container>
Container& operator | (Container& a, TransformOp op) {
    __typeof(a) values;
    switch (op) {
        case ADD_1:
            for (auto& elem : a) elem += 1;
            break;
        case COMPRESS:
            values = a;
            std::sort(values.begin(), values.end());
            values.erase(std::unique(values.begin(), values.end()), values.end());
            for (auto& value : a) value = std::lower_bound(values.begin(), values.end(), value) - values.begin();
            break;
        case PREFIX_SUM:
            std::partial_sum(a.begin(), a.end(), a.begin());
            break;
        case PREFIX_SUM_XOR:
            std::partial_sum(a.begin(), a.end(), a.begin(), [] (int x, int y) { return x ^ y; });
            break;
        case REVERSE:
            std::reverse(a.begin(), a.end());
            break;
        case SUB_1:
            for (auto& elem : a) elem -= 1;
            break;
    }
    return a;
}
enum IOp { IN };
template<typename Container>
Container& operator | (Container& a, IOp op) {
    switch (op) {
        case IN:
            for (auto& elem : a) cin >> elem;
            break;
    }
    return a;
}
enum OOp { OUT_ONE_PER_LINE, OUT_1_LINE };
template<typename Container>
Container& operator | (Container& a, OOp op) {
    switch (op) {
        case OUT_1_LINE:
            for (size_t i = 0; i < a.size(); ++i) {
                if (i > 0) cout << ' ';
                cout << a[i];
            }
            break;
        case OUT_ONE_PER_LINE:
            for (const auto& elem : a) cout << elem << '\n';
            break;
    }
    return a;
}
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
    int nRow, nCol; cin >> nRow >> nCol;
    vector<vector<int>> a;
    if (nCol <= nRow) {
        a = vector<vector<int>> (nRow, vector<int> (nCol));
        REP(i,nRow) REP(j,nCol) cin >> a[i][j];
    } else {
        swap(nRow, nCol);
        a = vector<vector<int>> (nRow, vector<int> (nCol));
        REP(j,nCol) FORD(i,nRow-1,0) cin >> a[i][j];
    }

    int res = 0;
    FOR(c1,0,nCol-1) FOR(c2,c1+1,nCol-1) {
        vector<vector<int>> ups(nRow);
        Fenwick<int> fen(nRow);

        REP(r2,nRow) {
            if (a[r2][c2] < c2 - c1) continue;
            int val = max(r2 - a[r2][c1], 0);
            ups[val].push_back(r2);
        }

        FOR(r1,0,nRow-1) {
            for (int r : ups[r1]) {
                fen.update(r, +1);
            }
            if (a[r1][c1] < c2 - c1) continue;

            res += fen.get(r1+1, min(nRow-1, r1+a[r1][c2]) + 1);
        }
    }
    cout << res << endl;
}
