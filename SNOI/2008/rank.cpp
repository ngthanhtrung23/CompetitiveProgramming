// Algo: topo sort

// template {{{
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define FORD(i,a,b) for(int i=(a),_##i##_b=(b); i>=_##i##_b; i--)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))
#define ALL(s) (s).begin(), (s).end()

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
    for (int& x : res) cin >> x;
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

// Topo sort
// returns: <has topo sort?, topo order>
std::pair<bool, std::vector<int>> topo_sort(const std::vector<std::vector<int>>& g) {
    int n = g.size();
    // init in_deg
    std::vector<int> in_deg(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : g[u]) {
            in_deg[v]++;
        }
    }

    // find topo order
    std::vector<int> res;
    std::queue<int> qu;
    for (int u = 0; u < n; u++) {
        if (in_deg[u] == 0) {
            qu.push(u);
        }
    }

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        res.push_back(u);
        for (int v : g[u]) {
            in_deg[v]--;
            if (in_deg[v] == 0) {
                qu.push(v);
            }
        }
    }

    if ((int) res.size() < n) {
        return {false, {}};
    }
    return {true, res};
}

void solve() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<int>> g(n);
    while (m--) {
        char c1, c2;
        int x, y, z;
        scanf("%d%c%d%c%d", &x, &c1, &y, &c2, &z);
        --x; --y; --z;

        if (c1 == '>') {
            g[x].push_back(y);
            g[x].push_back(z);
        } else if (c2 == '>') {
            g[x].push_back(z);
            g[y].push_back(z);
        } else {
            assert(false);
        }
    }
    auto [has, topo] = topo_sort(g);
    if (!has) cout << 0 << endl;
    else {
        for (int u : topo) cout << 1+u << ' ';
        cout << endl;
    }
}
