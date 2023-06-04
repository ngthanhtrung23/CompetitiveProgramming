// Algo: greedy, coin exchange

// template {{{
#include <bits/stdc++.h>
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

void solve() {
    I(n5);
    I(n10);
    I(n20);
    I(n50);
    I(need);

    const int INF = INT_MAX;
    int res = INF;

    tuple<int,int,int,int> save;
    FOR(use50,0,n50) {
        int x = need - 50 * use50;
        if (x < 0) continue;  // used too many 50

        int total_used = use50;

        // For 5, 10, 20, we can greedily use the coins
        // since 20 % 10 == 0 and 10 % 5 == 0
        int use20 = min(x / 20, n20);
        total_used += use20;
        x -= use20 * 20;
        assert(x >= 0);

        int use10 = min(x / 10, n10);
        total_used += use10;
        x -= use10 * 10;
        assert(x >= 0);

        int use5 = min(x / 5, n5);
        total_used += use5;
        x -= use5 * 5;

        if (x == 0 && total_used < res) {
            res = total_used;
            save = {use5, use10, use20, use50};
        }
    }

    if (res == INF) cout << -1 << endl;
    else {
        auto [use5, use10, use20, use50] = save;
        cout << use5 << ' ' << use10 << ' ' << use20 << ' ' << use50 << ' ' << res << endl;
    }
}
