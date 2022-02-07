// Statement: in comments in https://codeforces.com/blog/entry/98670
//
// Idea:
// f[u] = min cost to go from 1 -> i
// f[u] = min(f[p] + r[p] + c[p] * (h[u] - h[p]))
//      = min( (f[p] + r[p] - c[p] * h[p]) + c[p] * h[u])
//
// We can use persistent LiChao tree to maintain lines of the form ax + b
// where:
//   a = c[p]
//   b = f[p] + r[p] - c[p] * h[p]

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

typedef int num_t;
const num_t oo = (num_t) 1e18;
struct func_t {
    num_t a, b;
    func_t(num_t a = 0, num_t b = oo) : a(a), b(b) {}
    num_t query(num_t x) {return a * x + b;}
};
struct node_t {
    node_t *l, *r;
    func_t f;
    node_t(node_t* l = 0, node_t* r = 0, func_t f = func_t()) : l(l), r(r), f(f) {}
    num_t query(num_t x) {return f.query(x);}
};
node_t* upd(node_t* p, int l, int r, int L, int R, func_t f) {
    if (l > R || r < L) return p;
    int M = L + (R - L >> 1);
    node_t* res = p ? new node_t(p->l, p->r, p->f) : new node_t();
    if (l <= L && r >= R) {
        int fl = f.query(L) >= (p ? p->query(L) : oo);
        int fr = f.query(R) >= (p ? p->query(R) : oo);
        if (fl && fr) return res;
        if (!fl && !fr) {
            res->f = f;
            return res;
        }
        int fm1 = f.query(M) >= (p ? p->query(M) : oo);
        if (fl && fm1) {
            res->r = upd(res->r, l, r, M + 1, R, f);
            return res;
        }
        if (!fl && !fm1) {
            res->r = upd(res->r, l, r, M + 1, R, res->f);
            res->f = f;
            return res;
        }
        int fm2 = f.query(M + 1) >= (p ? p->query(M + 1) : oo);
        if (fm2 && fr) {
            res->l = upd(res->l, l, r, L, M, f);
            return res;
        }
        if (!fm2 && !fr) {
            res->l = upd(res->l, l, r, L, M, res->f);
            res->f = f;
            return res;
        }
        assert(0);
    }
    res->l = upd(res->l, l, r, L, M, f);
    res->r = upd(res->r, l, r, M + 1, R, f);
    return res;
}
node_t* upd(node_t* p, int l, int r, int L, int R, num_t a, num_t b) {
    return upd(p, l, r, L, R, func_t(a, b));
}
num_t query(node_t* p, int i, int L, int R) {
    if (!p) return oo;
    if (i < L || i > R) return oo;
    num_t res = p->query(i);
    if (L < R) {
        res = min(res, query(p->l, i, L, L + R >> 1));
        res = min(res, query(p->r, i, (L + R >> 1) + 1, R));
    }
    return res;
}

const int MN = 200111;
vector<pair<int,int>> ke[MN];
int h[MN], par[MN], f[MN];
pair<int,int> cost[MN];

node_t* tree[MN];

void dfs1(int u, int fu) {
    par[u] = fu;

    for (auto [v, c] : ke[u]) {
        if (v == fu) continue;

        h[v] = h[u] + c;
        dfs1(v, u);
    }
}

int max_height;
void dfs2(int u, int fu) {
    if (u == 1) {
        f[u] = 0;
    } else {
        f[u] = query(tree[fu], h[u], 0, max_height);
    }
    int a = cost[u].second;
    int b = f[u] + cost[u].first - cost[u].second * h[u];
    if (u != 1) {
        tree[u] = upd(tree[fu], 0, max_height, 0, max_height, a, b);
    } else {
        tree[u] = upd(tree[u], 0, max_height, 0, max_height, a, b);
    }

    for (auto [v, c] : ke[u]) {
        if (v == fu) continue;
        dfs2(v, u);
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    REP(_,n-1) {
        int u, v, c; cin >> u >> v >> c;
        ke[u].emplace_back(v, c);
        ke[v].emplace_back(u, c);
    }
    FOR(i,1,n) {
        cin >> cost[i].second >> cost[i].first;
    }
    dfs1(1, -1);
    max_height = *max_element(h+1, h+n+1);

    tree[1] = new node_t;

    dfs2(1, -1);
    FOR(i,2,n) cout << f[i] << ' ';
    cout << endl;
    return 0;
}

