#include "bits/stdc++.h"
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx2,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

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

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int r) {
    return uniform_int_distribution<int> (0, r-1)(rng);
}

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MN = 200111;
int g[MN];  // longest path from u, outside subtree(u)
int f[MN];  // longest path from u, inside subtree(u)
int parent[MN];
vector<int> adj[MN];
vector<int> paths_from_u[MN];

// compute f[u]
void dfs1(int u, int fu) {
    parent[u] = fu;
    f[u] = 0;
    for (int v : adj[u]) {
        if (v == fu) continue;

        dfs1(v, u);
        f[u] = max(f[u], f[v] + 1);
    }
}

// compute g[u], using reroot tree DP
void dfs2(int u, int fu) {
    // prefix and suffix max, for f(children(u))
    vector<int> left, right;
    for (int v : adj[u]) {
        if (v == fu) {
            left.push_back(g[u]);
        } else {
            left.push_back(f[v] + 1);
        }
    }
    right = left;
    for (int i = 1; i < SZ(left); i++) {
        left[i] = max(left[i-1], left[i]);
    }
    for (int i = SZ(right) - 2; i >= 0; i--) {
        right[i] = max(right[i+1], right[i]);
    }

    // compute g(children)
    REP(i,SZ(adj[u])) {
        int v = adj[u][i];
        if (v == fu) continue;

        // v -> u
        g[v] = 1;
        // v -> u -> left of v
        if (i > 0) g[v] = max(g[v], left[i-1] + 1);
        if (i+1 < SZ(adj[u])) g[v] = max(g[v], right[i+1] + 1);

        dfs2(v, u);
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    FOR(i,1,n-1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1, -1);
    dfs2(1, -1);

    FOR(u,1,n) {
        for (int v : adj[u]) {
            if (v == parent[u]) paths_from_u[u].push_back(g[u]);
            else paths_from_u[u].push_back(f[v] + 1);
        }
        sort(paths_from_u[u].begin(), paths_from_u[u].end());
    }
    while (q--) {
        int u, x; cin >> u >> x;
        auto it = lower_bound(paths_from_u[u].begin(), paths_from_u[u].end(), x+1);
        cout << paths_from_u[u].end() - it << '\n';
    }

    return 0;
}
