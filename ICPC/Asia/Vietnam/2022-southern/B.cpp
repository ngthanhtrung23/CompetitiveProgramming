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
// Link Cut Tree {{{
// copied from https://codeforces.com/blog/entry/75885
// - Index from 1
// - T needs to support + operation
//   For subtree queries -> requires - operation
//   --> see this comment for how to handle it: https://codeforces.com/blog/entry/67637?#comment-650424
// - Not using template here, since inheritance becomes very ugly
// - Doesn't support lazy update (so no subtree updates)
//
// Tested:
// - https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum
// - https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
// - https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum

// Add this for path queries only
#define PATH_QUERIES_ONLY

const int INF = 1e9 + 11;
struct T {
    int x = INF;
};
T operator + (const T&a, const T& b) {
    return T{ min(a.x, b.x) };
}

// SplayTree {{{
struct SplayTree { // can we replace SplayTreeById and use this only?
    struct Node {
        array<int, 2> child = {0, 0};
        int parent = 0;

        // Path aggregates
        // - path[0] = go from left -> right
        // - path[1] = go from right -> left
        array<T, 2> path;  // default to T constructor
        T self;

        // Subtree aggregates
        T sub, vir;

        bool reverse = false;
    };
    vector<Node> nodes;

    SplayTree(int n) : nodes(n + 1) {}

    void splay(int x) {
        for (pushDown(x); ~getDirection(x); ) {
            int y = nodes[x].parent;
            int z = nodes[y].parent;
            pushDown(z);
            pushDown(y);
            pushDown(x);
            int dx = getDirection(x);
            int dy = getDirection(y);
            if (~dy) rotate(dx != dy ? x : y);
            rotate(x);
        }
    }

// private:
    // Return t where nodes[parent(x)].child[t] == x
    int getDirection(int x) {
        int p = nodes[x].parent;
        if (!p) return -1;
        return nodes[p].child[0] == x ? 0 : nodes[p].child[1] == x ? 1 : -1;
    }

    /**
     * Before:
     *    z
     *    |
     *    y
     *   /
     *  x
     *   \
     *   xchild
     * 
     * After:
     *    z
     *    |
     *    x
     *     \
     *      y
     *     /
     *   xchild
     */
    void rotate(int x) {
        int y = nodes[x].parent, dx = getDirection(x);
        int z = nodes[y].parent, dy = getDirection(y);

        setChild(y, nodes[x].child[!dx], dx);
        setChild(x, y, !dx);
        if (~dy) setChild(z, x, dy);
        nodes[x].parent = z;
    }

    void pushDown(int x) {
        if (!x) return;
        if (nodes[x].reverse) {
            auto [l, r] = nodes[x].child;
            nodes[l].reverse ^= 1;
            nodes[r].reverse ^= 1;

            swap(nodes[x].child[0], nodes[x].child[1]);
            swap(nodes[x].path[0], nodes[x].path[1]);
            nodes[x].reverse = false;
        }
    }

    void pushUp(int x) {
        auto [l, r] = nodes[x].child;
        pushDown(l); pushDown(r);

        nodes[x].path[0] = nodes[l].path[0] + nodes[x].self + nodes[r].path[0];
        nodes[x].path[1] = nodes[r].path[1] + nodes[x].self + nodes[l].path[1];

        nodes[x].sub = nodes[x].vir + nodes[l].sub + nodes[r].sub + nodes[x].self;
    }

    void setChild(int x, int y, int dir) {
        nodes[x].child[dir] = y;
        nodes[y].parent = x;
        pushUp(x);
    }
};
// }}}

struct LinkCut : SplayTree {
    LinkCut(int n) : SplayTree(n) {}

    void link(int u, int v) {
        reroot(u);
        access(v);

        nodes[v].vir = nodes[v].vir + nodes[u].sub;
        nodes[u].parent = v;
        pushUp(v);
    }

    void cut(int u, int v) {
        reroot(u);
        access(v);

        nodes[v].child[0] = nodes[u].parent = 0;
        pushUp(v);
    }

    // Returns 0 if u and v are not connected
    int LCA(int u, int v) {
        if (u == v) return u;
        access(u);
        int ret = access(v);
        return nodes[u].parent ? ret : 0;
    }

    T getPath(int u, int v) {
        reroot(u);
        access(v);
        return nodes[v].path[1];
    }

    void set(int u, T val) {
        access(u);
        nodes[u].self = val;
        pushUp(u);
    }

    T get(int u) {
        return nodes[u].self;
    }

    // Get aggregate of subtree(u). v is parent of u. There must exist edge(v, u) (?)
    T getSubtree(int u, int v) {
        reroot(v); access(u);
        return nodes[u].vir + nodes[u].self;
    }

// private:
    void reroot(int x) {
        access(x);
        nodes[x].reverse ^= 1;
        pushDown(x);
    }

    int access(int x) {
        int u = x, v = 0;
        for (; u; v = u, u = nodes[u].parent) {
            splay(u);
            int& ov = nodes[u].child[1];
            nodes[u].vir = nodes[u].vir + nodes[ov].sub;
#ifndef PATH_QUERIES_ONLY
            // T requires subtract for subtree queries
            nodes[u].vir -= nodes[v].sub;
#endif

            ov = v; pushUp(u);
        }
        return splay(x), v;
    }
};

// Example for custom type: // https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
// Since T doesn't support subtract -> comment out line
//   nodes[u].vir -= nodes[v].sub
/**
struct T {
    modular a, b;

    T() : a(1), b(0) {}
    T(modular _a, modular _b) : a(_a), b(_b) {}

    // return f(g())
    T operator + (const T& g) const {
        return T {
            a * g.a,
            a * g.b + b,
        };
    }

    T operator += (const T& g) {
        b = a * g.b + b;
        a = a * g.a;
        return *this;
    }
};
*/
// }}}

struct Query {
    char typ;
    int u, v, w;
};
struct Edge {
    int u, v, c;
    int id;
};
ostream& operator << (ostream& out, const Edge& e) {
    out << e.u << ' ' << e.v << " [" << e.c << "]";
    return out;
}
Edge edges[100111];

// MST {{{
set<int> to_set(const vector<int>& v) {
    return set<int> (v.begin(), v.end());
}
set<int> get_ids(int n) {
    vector<int> res(n);
    std::iota(res.begin(), res.end(), 1);
    return to_set(res);
}
template<typename Container>
set<int> mst(int n, const Container& ids) {
    vector<Edge> es;
    for (auto id : ids) {
        es.push_back(edges[id]);
    }

    sort(es.begin(), es.end(),
            [&] (const Edge& a, const Edge& b) { return a.c > b.c; });
    DSU dsu(n + 1);
    vector<int> res;

    for (auto e : es) {
        if (dsu.merge(e.u, e.v)) {
            res.push_back(e.id);
        }
    }

    return to_set(res);
}
// }}}

void solve() {
    int n, nEdge, nQuery; cin >> n >> nEdge >> nQuery;
    // read edges {{{
    FOR(i,1,nEdge) {
        cin >> edges[i].u >> edges[i].v >> edges[i].c;
        edges[i].id = i;
    }
    // }}}

    // Find MST
    set<int> edge_ids = get_ids(nEdge);
    set<int> mst_edge_ids = mst(n, edge_ids);

    /*
    cout << "MST: " << endl;
    for (auto id : mst_edge_ids) DEBUG(edges[id]);
    */
    
    // Build LinkCut tree on top of MST
    auto get_link_cut_tree = [&] (const std::set<int> mst_edge_ids) {
        LinkCut tree(n + SZ(mst_edge_ids));
        for (int i = 1; i <= n; ++i) tree.set(i, T{INF});
        int id = n;
        for (int i : mst_edge_ids) {
            ++id;
            tree.set(id, T{edges[i].c});
            tree.link(edges[i].u, id);
            tree.link(edges[i].v, id);
        }
        return tree;
    };
    auto tree = get_link_cut_tree(mst_edge_ids);

    // read queries and remove updated edges from edge_ids {{{
    vector<Query> queries(nQuery);
    set<int> updated_edge_ids;
    for (auto& query : queries) {
        cin >> query.typ;
        if (query.typ == 'S') {
            cin >> query.u >> query.v >> query.w;
        } else {
            assert(query.typ == 'C');
            cin >> query.u >> query.w;
            edge_ids.erase(query.u);
            updated_edge_ids.insert(query.u);
        }
    }
    // }}}

    // Removed all updated edges. Find MST again
    // DEBUG(edge_ids);
    set<int> new_mst_edge_ids = mst(n, edge_ids);

    // make mst_edge_ids contain all possible MST edges
    mst_edge_ids.insert(new_mst_edge_ids.begin(), new_mst_edge_ids.end());
    mst_edge_ids.insert(updated_edge_ids.begin(), updated_edge_ids.end());
    // DEBUG(SZ(mst_edge_ids));
    // for (auto id : mst_edge_ids) DEBUG(edges[id]);

    for (const auto& query : queries) {
        if (query.typ == 'S') {
            if (tree.LCA(query.u, query.v) == 0) {
                // not connected
                cout << "NO\n";
                continue;
            }
            int min_weight = tree.getPath(query.u, query.v).x;
            cout << (min_weight >= query.w ? "YES" : "NO") << '\n';
        } else {
            edges[query.u].c = query.w;
            auto mst_ids = mst(n, mst_edge_ids);
            tree = get_link_cut_tree(mst_ids);
            /*
            cout << "New MST: " << endl;
            for (auto id : mst_ids) DEBUG(edges[id]);
            */
        }
    }
}
