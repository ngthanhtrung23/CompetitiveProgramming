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
// DisjointSet {{{
struct DSU {
    vector<int> lab;

    DSU(int n) : lab(n+1, -1) {}

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }

    bool same_component(int u, int v) {
        return getRoot(u) == getRoot(v);
    }

    int component_size(int u) {
        return -lab[getRoot(u)];
    }
};
// }}}

template <typename T>
std::vector<std::tuple<T, int, int>> manhattan_mst(std::vector<T> xs, std::vector<T> ys) {
    const int n = xs.size();
    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::vector<std::tuple<T, int, int>> ret;
    for (int s = 0; s < 2; s++) {
        for (int t = 0; t < 2; t++) {
            auto cmp = [&](int i, int j) { return xs[i] + ys[i] < xs[j] + ys[j]; };
            std::sort(idx.begin(), idx.end(), cmp);
            std::map<T, int> sweep;
            for (int i : idx) {
                for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end(); it = sweep.erase(it)) {
                    int j = it->second;
                    if (xs[i] - xs[j] < ys[i] - ys[j]) break;
                    ret.emplace_back(std::abs(xs[i] - xs[j]) + std::abs(ys[i] - ys[j]), i, j);
                }
                sweep[-ys[i]] = i;
            }
            std::swap(xs, ys);
        }
        for (auto &x : xs) x = -x;
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}

void solve() {
#ifndef RR
    freopen("INTERNET.INP", "r", stdin);
    freopen("INTERNET.OUT", "w", stdout);
#endif
    int n, s, k;
    cin >> n >> s >> k;
    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        cin >> xs[i] >> ys[i];
    }

    auto edges = manhattan_mst(xs, ys);
    // Find minimum spanning tree
    DSU dsu(n);
    int sum = 0;
    for (auto [cost, u, v] : edges) {
        if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

        dsu.merge(u, v);
        if (cost > s) {
            sum += cost;
            --k;
            if (k == 0) break;
        }
    }
    cout << sum << endl;
}
