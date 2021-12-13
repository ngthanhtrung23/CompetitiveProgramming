#include "bits/stdc++.h"
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")
using namespace std;

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

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MN = 200111;
int a[MN];
int n, q;
vector<int> g[MN];

struct Node {
    // increasing seq, if we go from left / from right
    vector<int> left, right;
} nodes[MN * 4];

Node combine(const Node& leftChild, const Node& rightChild) {
    Node res;

    res.left = leftChild.left;
    for (int x : rightChild.left) {
        if (x > res.left.back()) {
            res.left.push_back(x);
        }
    }

    res.right = rightChild.right;
    for (int x : leftChild.right) {
        if (x > res.right.back()) {
            res.right.push_back(x);
        }
    }

    return res;
}

int querySTFromLeft(int i, int l, int r, int u, int v, int& last) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) {
        int res = nodes[i].left.end()
            - upper_bound(nodes[i].left.begin(), nodes[i].left.end(), last);
        if (res) last = nodes[i].left.back();
        return res;
    }
    int mid = (l + r) / 2;
    return querySTFromLeft(i*2, l, mid, u, v, last)
        + querySTFromLeft(i*2+1, mid+1, r, u, v, last);
}

int querySTFromRight(int i, int l, int r, int u, int v, int& last) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) {
        int res = nodes[i].right.end()
            - upper_bound(nodes[i].right.begin(), nodes[i].right.end(), last);
        if (res) last = nodes[i].right.back();
        return res;
    }
    int mid = (l + r) / 2;
    return querySTFromRight(i*2+1, mid+1, r, u, v, last)
        + querySTFromRight(i*2, l, mid, u, v, last);
}

// for HLD
int parent[MN], depth[MN];
int in[MN], out[MN], nxt[MN], sz[MN], dfs_number, order[MN];

void dfs_parent(int v, int pv) {
    parent[v] = pv;
    for (int u : g[v]) {
        if (u != pv) {
            depth[u] = depth[v] + 1;
            dfs_parent(u, v);
        }
    }
}

void dfs_sz(int v) {
    sz[v] = 1;
    for(auto &u: g[v]) {
        dfs_sz(u);
        sz[v] += sz[u];
        if(sz[u] > sz[g[v][0]])
            swap(u, g[v][0]);
    }
}

void dfs_hld(int v) {
    order[dfs_number] = v;
    in[v] = dfs_number++;
    for(auto u: g[v]) {
        nxt[u] = (u == g[v][0] ? nxt[v] : u);
        dfs_hld(u);
    }
    out[v] = dfs_number;
}

// return true if u is ancestor of v
bool isAncestor(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

// Return all segment on path from u -> v
// For this problem, the order (u -> v is different from v -> u)
vector< pair<int,int> > getSegments(int u, int v) {
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

int query(int start, int target) {
    auto segments = getSegments(start, target);
    // DEBUG(segments);

    int res = 0;
    int last = 0;
    for (auto [u, v] : segments) {
        if (in[u] <= in[v]) {
            res += querySTFromLeft(1, 1, n, in[u], in[v], last);
        } else {
            res += querySTFromRight(1, 1, n, in[v], in[u], last);
        }
    }
    return res;
}

// build Segment Tree
void build(int i, int l, int r) {
    if (l == r) {
        nodes[i].left.push_back(a[order[l]]);
        nodes[i].right.push_back(a[order[r]]);
        return;
    }
    int mid = (l + r) / 2;
    build(i*2, l, mid);
    build(i*2+1, mid+1, r);

    nodes[i] = combine(nodes[i*2], nodes[i*2+1]);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n-1) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    depth[1] = 1;
    dfs_parent(1, -1);
    FOR(i,1,n) {
        auto it = std::find(g[i].begin(), g[i].end(), parent[i]);
        if (it != g[i].end()) g[i].erase(it);
    }

    // init heavy light
    dfs_number = 1;
    nxt[1] = 1;
    dfs_sz(1);
    dfs_hld(1);

    // build SegTree
    build(1, 1, n);

    int p = 0;
    while (q--) {
        int x, y; cin >> x >> y;
        int s = (x + p) % n + 1;
        int t = (y + p) % n + 1;

        p = query(s, t);
        cout << p << '\n';
    }
    return 0;
}

