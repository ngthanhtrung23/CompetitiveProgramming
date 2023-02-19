
/**
 * a = set of unique endpoints
 * In optimal solutions: both endpoints are in `a`
 *
 * Data structure need to maintain:
 * - f(L) = optimal sum if left endpoint == L
 *
 * for r = 0 .. |a| - 1
 * - R = a(r)
 * - segs[i]: L <= segs[i].l => update += segs[i].w
 * - compute max(0..r)
 */

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

struct Seg {
    int l, r, w;
};

struct Node {
    int ln, lazy;

    void add(int val) {
        ln += val;
        lazy += val;
    }
} nodes[2000111];

void up(int i) {
    nodes[i].ln = max(nodes[2*i].ln, nodes[2*i+1].ln);
}
void down(int i) {
    if (nodes[i].lazy) {
        nodes[2*i].add(nodes[i].lazy);
        nodes[2*i+1].add(nodes[i].lazy);

        nodes[i].lazy = 0;
    }
}

const int INF = 100011100011100LL;

// nodes(i) [l, r]
int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return -INF;
    if (u <= l && r <= v) return nodes[i].ln;

    down(i);
    int mid = (l + r) / 2;
    int res = max(get(i*2, l, mid, u, v),
            get(i*2+1, mid+1, r, u, v));
    up(i);

    return res;
}

// nodes(i) [l, r]
void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return;
    if (u <= l && r <= v) {
        nodes[i].add(val);
        return;
    }

    down(i);
    int mid = (l + r) / 2;
    update(i*2, l, mid, u, v, val);
    update(i*2+1, mid+1, r, u, v, val);
    up(i);
}

void solve() {
#ifndef RR
    freopen("SSEQ.INP", "r", stdin);
    freopen("SSEQ.OUT", "w", stdout);
#endif

    int n; cin >> n;
    vector<Seg> segs(n);
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        cin >> segs[i].l >> segs[i].r >> segs[i].w;
        a.push_back(segs[i].l);
        a.push_back(segs[i].r);
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    int s = a.size();
    a.insert(a.begin(), -1000111000);

    auto get_id = [&] (int val) {
        return lower_bound(a.begin(), a.end(), val) - a.begin();
    };

    vector<vector<int>> ends_at(a.size());
    for (int i = 0; i < n; ++i) {
        int r = get_id(segs[i].r);
        ends_at[r].push_back(i);
    }

    int res = 0;
    for (int r = 1; r <= s; ++r) {
        for (int i : ends_at[r]) {
            int l = get_id(segs[i].l);
            update(1, 1, s, 1, l, segs[i].w);
        }

        int cur = get(1, 1, s, 1, r);
        res = max(res, cur);
    }
    cout << res << endl;
}
