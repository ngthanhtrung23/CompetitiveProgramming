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
// 1D Fenwick {{{
// 0 based index
//
// Tested:
// - https://judge.yosupo.jp/problem/static_range_sum
// - https://judge.yosupo.jp/problem/point_add_range_sum
template<
    typename T  // need to support operators + -
> struct Fenwick {
    Fenwick(int _n) : n(_n), f(_n + 1) {}

    // a[u] += val
    void update(int u, T val) {
        assert(0 <= u && u < n);
        ++u;
        for (; u <= n; u += u & -u) {
            f[u] += val;
        }
    }

    // return a[0] + .. + a[u-1]
    T get(int u) const {
        assert(0 <= u && u <= n);
        T res = 0;
        for (; u > 0; u -= u & -u) {
            res += f[u];
        }
        return res;
    }

    // return a[l] + .. + a[r-1]
    T get(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return 0;  // empty
        return get(r) - get(l);
    }

    void reset() {
        std::fill(f.begin(), f.end(), T(0));
    }

    int n;
    vector<T> f;
};
// }}}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    vector<Fenwick<int>> fens;
    vector<vector<int>> ids(n + 1);

    REP(i,n) {
        cin >> a[i];
        ids[a[i]].push_back(i);
    }
    FOR(val,0,n) {
        fens.push_back(Fenwick<int> (SZ(ids[val])));
        REP(i,SZ(ids[val])) {
            int id = ids[val][i];
            fens[val].update(i, sqr(id+1));
        }
    }

    int last = 0;
    while (q--) {
        int typ; cin >> typ;
        if (typ == 1) {
            int pp; cin >> pp;
            int p = (pp + last - 1) % (n-1);

            if (a[p] == a[p+1]) continue;

            auto upd = [&] (int p, int dir, int diff) {
                int u = lower_bound(ids[a[p]].begin(), ids[a[p]].end(), p) - ids[a[p]].begin();
                assert(ids[a[p]][u] == p);
                assert(fens[a[p]].get(u, u+1) == sqr(p+1));

                ids[a[p]][u] += dir;
                fens[a[p]].update(u, diff);
            };
            upd(p, +1, sqr(p+2) - sqr(p+1));
            upd(p+1, -1, sqr(p+1) - sqr(p+2));

            swap(a[p], a[p+1]);
        } else {
            int ll, rr, xx; cin >> ll >> rr >> xx;
            int l = (ll + last - 1) % n;
            int r = (rr + last - 1) % n;
            int x = (xx + last - 1) % n + 1;
            if (l > r) swap(l, r);

            if (typ == 3) {
                assert(0 <= l);
                assert(l <= r);
                assert(r < SZ(ids[x]));

                last = fens[x].get(l, r+1);
            } else {
                assert(typ == 2);
                l = lower_bound(ids[x].begin(), ids[x].end(), l) - ids[x].begin();
                r = upper_bound(ids[x].begin(), ids[x].end(), r) - ids[x].begin();

                last = fens[x].get(l, r);
            }

            cout << last << '\n';
        }
    }
}
