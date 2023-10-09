// template {{{
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

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

template<typename T>
vector<T> read_vector(int n) {
    vector<T> res(n);
    for (int& x : res) cin >> x;
    return res;
}

void solve();

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}
// }}}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> g(n);
    while (m--) {
        int u, v; cin >> u >> v;
        --u; --v;
        g[u].emplace_back(v, -1);
        g[v].emplace_back(u, -1);
    }
    int k; cin >> k;
    while (k--) {
        int t, u, v; cin >> t >> u >> v;
        --u; --v;
        g[u].emplace_back(v, t);
        g[v].emplace_back(u, t);
    }

    vector<int> dist(n, -1);
    dist[0] = 0;
    set<pair<int,int>> all;
    all.insert({0, 0});

    while (!all.empty()) {
        auto [d, u] = *all.begin();
        all.erase(all.begin());

        if (d != dist[u]) continue;

        for (auto [v, t] : g[u]) {
            int cur = max(dist[u] + 1, t);
            if (dist[v] < 0 || dist[v] > cur) {
                dist[v] = cur;
                all.insert({dist[v], v});
            }
        }
    }
    cout << dist.back() << endl;
}
