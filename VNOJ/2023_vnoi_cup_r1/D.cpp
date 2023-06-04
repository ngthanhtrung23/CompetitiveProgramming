// template {{{
// CF pragma: https://codeforces.com/blog/entry/96344
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#ifndef UNSAFE_NO_DEFINE_INT_LONG_LONG
#define int long long
#endif
#define I(x) int x; cin >> x;
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define FORD(i,a,b) for(int i=(a),_##i##_b=(b); i>=_##i##_b; i--)
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

// }}}
// Container operations, idea from https://codeforces.com/submissions/Yuu {{{
template<typename T> struct accumulator_type { using type = T; };
template<> struct accumulator_type<int32_t> { using type = int64_t; };
template<> struct accumulator_type<uint32_t> { using type = uint64_t; };
template<> struct accumulator_type<int64_t> { using type = __int128_t; };
template<> struct accumulator_type<uint64_t> { using type = __uint128_t; };

enum ReduceOperator { MIN, MAX, CNT_MAX };
template<typename Container>
auto operator | (const Container& a, ReduceOperator op) {
    switch (op) {
        case MIN:
            return *min_element(a.begin(), a.end());
        case MAX:
            return *max_element(a.begin(), a.end());
        case CNT_MAX:
            auto ma = *max_element(a.begin(), a.end());
            int cnt = 0;
            for (const auto& elem : a) cnt += elem == ma;
            return cnt;
    }
    assert(false);
}
enum SumOperator { SUM, SUM_XOR };
template<typename Container>
auto operator | (const Container& a, SumOperator op) {
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
enum ComparableOperator { SORT };
template<typename Container>
Container& operator | (Container& a, ComparableOperator op) {
    __typeof(a) values;
    switch (op) {
        case SORT:
            std::sort(a.begin(), a.end());
            break;
    }
    return a;
}
enum TransformOperator { ADD_1, PREFIX_SUM, PREFIX_SUM_XOR, REVERSE, SUB_1, COMPRESS };
template<typename Container>
Container& operator | (Container& a, TransformOperator op) {
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
enum IOOperator { IN, OUT_ONE_PER_LINE, OUT_1_LINE };
template<typename Container>
Container& operator | (Container& a, IOOperator op) {
    switch (op) {
        case IN:
            for (auto& elem : a) cin >> elem;
            break;
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

struct Counter {
    int cnt[300];
    int n_bad = 0;

    void add(char c) {
        if (cnt[c] == 0) ++n_bad;
        ++cnt[c];
        if (cnt[c] == 0) --n_bad;
    }
    void rem(char c) {
        if (cnt[c] == 0) ++n_bad;
        --cnt[c];
        if (cnt[c] == 0) --n_bad;
    }
} counter;

void solve() {
    int n, k; cin >> n >> k;
    string s, t; cin >> s >> t;
    vector<int> a(n); a | IN | PREFIX_SUM;
    auto get_sum = [&] (int l, int r) {
        if (!l) return a[r];
        return a[r] - a[l-1];
    };
    
    int i = 0;
    vector<pair<int,int>> gaps;
    int res = 0;
    int cnt_seg = 0;
    int last_combine = -10;
    while (i < n) {
        int j = i;
        counter.add(s[i]);
        counter.rem(t[i]);

        while (j + 1 < n && counter.n_bad) {
            ++j;
            counter.add(s[j]);
            counter.rem(t[j]);
        }
        assert(counter.n_bad == 0);

        if (i == j) {
            if (gaps.empty() || gaps.back().second + 1 < i) gaps.emplace_back(i, i);
            else gaps.back().second++;
        } else {
            res += get_sum(i, j);
            if (last_combine + 1 < i) ++cnt_seg;
            last_combine = j;
        }

        i = j + 1;
    }
    vector<int> gap_costs;
    for (auto [l, r] : gaps) {
        if (l == 0 || r == n-1) continue;
        gap_costs.push_back(get_sum(l, r));
    }
    gap_costs | SORT;

    int need = cnt_seg - k;
    REP(i,need) {
        res += gap_costs[i];
    }

    cout << res << endl;
}
