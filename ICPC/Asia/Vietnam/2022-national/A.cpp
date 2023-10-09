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
// struct Query: typ, s, u, v {{{
struct Query {
    char typ;
    int s, u, v;

    bool ans;
};
istream& operator >> (istream& cin, Query& q) {
    cin >> q.typ;
    switch (q.typ) {
        case 'Q':
            return cin >> q.s >> q.u >> q.v;
        case 'A':
        case '?':
            return cin >> q.u >> q.v;
        case 'C':
            return cin;
        default:
            cout << "?? :@) ?? " << q.typ << endl;
            return cin;
    }
}
// }}}

void solve() {
    int n, nQuery; cin >> n >> nQuery;
    ++nQuery;
    vector<Query> queries(nQuery);
    queries[0].typ = 'C';

    // Read input & initialize snapshots
    int nSnapshot = 0;
    vector<vector<int>> queriesAtSnapshot(nQuery + 1);
    for (int qid = 1; qid < nQuery; ++qid) {
        auto& q = queries[qid];
        cin >> q;  // read q.typ, q.s, q.u, q.v

        if (q.typ == 'C') {
            ++nSnapshot;
        } else if (q.typ == 'Q') {
            assert(q.s <= nSnapshot);
            queriesAtSnapshot[q.s].push_back(qid);
        }
    }

    // Answer queries
    DSU dsu(n);
    nSnapshot = -1;
    for (auto& q : queries) {
        if (q.typ == 'A') {
            dsu.merge(q.u, q.v);
        } else if (q.typ == 'C') {
            ++nSnapshot;
            for (int qid : queriesAtSnapshot[nSnapshot]) {
                int u = queries[qid].u, v = queries[qid].v;
                queries[qid].ans = dsu.same_component(u, v);
            }
        } else if (q.typ == '?') {
            q.ans = dsu.same_component(q.u, q.v);
        }
    }

    // Print results
    for (const auto& q : queries) {
        if (q.typ == 'Q' || q.typ == '?') {
            cout << (q.ans ? 'Y' : 'N');
        }
    }
    cout << endl;
}
