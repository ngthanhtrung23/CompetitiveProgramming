// template {{{
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define I(x) int x; cin >> x;
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
#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)

template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
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
    srand(7777);
    solve();
    return 0;
}

// }}}
// HeavyLight {{{
struct HLD {
    HLD(const vector<vector<int>>& _g, int root)
            : n(_g.size()), g(_g),
            parent(n), depth(n), sz(n),
            dfs_number(0), nxt(n), in(n), out(n), order(n)
    {
        assert(0 <= root && root < n);

        // init parent, depth, sz
        // also move most heavy child of u to g[u][0]
        depth[root] = 0;
        dfs_sz(root, -1);

        // init nxt, in, out
        nxt[root] = root;
        dfs_hld(root);
    }

    int lca(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        while (true) {
            if (in[u] > in[v]) swap(u, v); // in[u] <= in[v]
            if (nxt[u] == nxt[v]) return u;
            v = parent[nxt[v]];
        }
    }

    // return k-th parent
    // if no such parent -> return -1
    int kth_parent(int u, int k) const {
        assert(0 <= u && u < n);
        if (depth[u] < k) return -1;

        while (true) {
            int v = nxt[u];
            if (in[u] - k >= in[v]) return order[in[u] - k];
            k -= in[u] - in[v] + 1;
            u = parent[v];
        }
    }

    // return k-th vertex on path from u -> v (0 <= k)
    // if k > distance -> return -1
    int kth_vertex_on_path(int u, int v, int k) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);

        int l = lca(u, v);
        int ul = depth[u] - depth[l];
        if (k <= ul) return kth_parent(u, k);
        k -= ul;
        int vl = depth[v] - depth[l];
        if (k <= vl) return kth_parent(v, vl - k);
        return -1;
    }

    int dist(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        int l = lca(u, v);
        return depth[u] + depth[v] - 2*depth[l];
    }

    // apply f on vertices on path [u, v]
    // edge = true -> apply on edge
    //
    // f(l, r) should update segment tree [l, r] INCLUSIVE
    void apply_path(int u, int v, bool edge, const function<void(int, int)> &f) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (u == v && edge) return;

        while (true) {
            if (in[u] > in[v]) swap(u, v); // in[u] <= in[v]
            if (nxt[u] == nxt[v]) break;
            f(in[nxt[v]], in[v]);
            v = parent[nxt[v]];
        }
        if (u == v && edge) return;
        f(in[u] + edge, in[v]);
    }

    // get prod of path u -> v
    // edge = true -> get on edges
    //
    // f(l, r) should query segment tree [l, r] INCLUSIVE
    // f must be commutative. For non-commutative, use getSegments below
    template<class S, S (*op) (S, S), S (*e)()>
    S prod_path_commutative(
            int u, int v, bool edge,
            const function<S(int, int)>& f) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (u == v && edge) {
            return e();
        }
        S su = e(), sv = e();
        while (true) {
            if (in[u] > in[v]) { swap(u, v); swap(su, sv); }
            if (nxt[u] == nxt[v]) break;
            sv = op(sv, f(in[nxt[v]], in[v]));
            v = parent[nxt[v]];
        }
        if (u == v && edge) {
            return op(su, sv);
        } else {
            return op(su, op(sv, f(in[u] + edge, in[v])));
        }
    }

    // f(l, r) modify seg_tree [l, r] INCLUSIVE
    void apply_subtree(int u, bool edge, const function<void(int, int)>& f) {
        assert(0 <= u && u < n);
        f(in[u] + edge, out[u] - 1);
    }

    // f(l, r) queries seg_tree [l, r] INCLUSIVE
    template<class S>
    S prod_subtree_commutative(int u, bool edge, const function<S(S, S)>& f) {
        assert(0 <= u && u < n);
        return f(in[u] + edge, out[u] - 1);
    }

    // Useful when functions are non-commutative
    // Return all segments on path from u -> v
    // For this problem, the order (u -> v is different from v -> u)
    vector< pair<int,int> > getSegments(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        vector< pair<int,int> > upFromU, upFromV;

        int fu = nxt[u], fv = nxt[v];
        while (fu != fv) {  // u and v are on different chains
            if (depth[fu] >= depth[fv]) { // move u up
                upFromU.push_back({u, fu});
                u = parent[fu];
                fu = nxt[u];
            } else { // move v up
                upFromV.push_back({fv, v});
                v = parent[fv];
                fv = nxt[v];
            }
        }
        upFromU.push_back({u, v});
        reverse(upFromV.begin(), upFromV.end());
        upFromU.insert(upFromU.end(), upFromV.begin(), upFromV.end());
        return upFromU;
    }

    // return true if u is ancestor
    bool isAncestor(int u, int v) const {
        return in[u] <= in[v] && out[v] <= out[u];
    }

// private:
    int n;
    vector<vector<int>> g;
    vector<int> parent;   // par[u] = parent of u. par[root] = -1
    vector<int> depth;    // depth[u] = distance from root -> u
    vector<int> sz;       // sz[u] = size of subtree rooted at u
    int dfs_number;
    vector<int> nxt;      // nxt[u] = vertex on heavy path of u, nearest to root
    vector<int> in, out;  // subtree(u) is in range [in[u], out[u]-1]
    vector<int> order;    // euler tour

    void dfs_sz(int u, int fu) {
        parent[u] = fu;
        sz[u] = 1;
        // remove parent from adjacency list
        auto it = std::find(g[u].begin(), g[u].end(), fu);
        if (it != g[u].end()) g[u].erase(it);

        for (int& v : g[u]) {
            depth[v] = depth[u] + 1;
            dfs_sz(v, u);

            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }

    void dfs_hld(int u) {
        order[dfs_number] = u;
        in[u] = dfs_number++;

        for (int v : g[u]) {
            nxt[v] = (v == g[u][0] ? nxt[u] : v);
            dfs_hld(v);
        }
        out[u] = dfs_number;
    }
};
// }}}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<vector<tuple<int,int,int>>> costs(n);
    FOR(i,1,n-1) {
        int u, v, cost_one, cost_multi;
        cin >> u >> v >> cost_one >> cost_multi;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        costs[u].emplace_back(v, cost_one, cost_multi);
        costs[v].emplace_back(u, cost_one, cost_multi);
    }

    HLD hld(adj, 0);
    vector<int> f(n, 0);
    for (int i = 1; i < n; ++i) {
        // we're currently at (i-1), traveling to i
        f[i-1]++;
        f[i]++;
        f[hld.lca(i-1, i)] -= 2;
    }

    int res = 0;
    function<void(int, int)> dfs = [&] (int u, int fu) {
        for (auto [v, cost_one, cost_multi] : costs[u]) {
            if (v == fu) continue;
            dfs(v, u);
            f[u] += f[v];
            res += min(cost_multi, f[v] * cost_one);
        }
    };

    dfs(0, -1);
    cout << res << endl;
}
