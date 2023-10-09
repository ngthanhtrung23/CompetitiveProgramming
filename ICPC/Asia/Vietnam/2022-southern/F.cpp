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

#define double long double
const int MN = 111;

struct Coin {
    double a, l, p, c, d;
    // If we initially have x0, and use this coin
    // -> pi * (x0 + ai) + (1-pi) * (1-li) * x0
    //  = x0 * (1 - li + pi*li) + pi*ai
    //
    // Let c = (1 - li + pi*li)
    //     d = pi*ai
    // => the effect of this coin is: x0*c + d
    Coin(double _a, double _l, double _p) : a(_a), l(_l), p(_p) {
        c = 1.0 - l + p*l; d = a*p;
    }
    Coin() {}
};
// Exchange argument
//     (Using coin u before coin v) is better than (using coin v before u)
// <=> (value after applying coin u then v) > (value after applying coin v then u)
// <=> (x0*u.c + u.d) * v.c + v.d > (x0*v.c + v.d) * u.c + u.d
// <=> u.d*v.c + v.d > v.d*u.c + u.d
bool operator < (const Coin& u, const Coin& v) { return u.d*v.c + v.d > v.d*u.c + u.d; }

Coin coins[MN];
double f[MN][MN];  // max expected value, if play i games using coins 1..j

void solve() {
    int n, k; double x0;
    while (cin >> n >> k >> x0 && n && k) {
        for (int i = 1; i <= n; ++i) {
            double a, l, p; cin >> a >> l >> p;
            coins[i] = Coin(a, l/100, p/100);
        }
        sort(coins+1, coins+n+1);

        memset(f, 0, sizeof f);
        for (int j = 0; j <= n; ++j) f[0][j] = x0;

        for (int i = 1; i <= k; ++i) {
            for (int j = i; j <= n; ++j) {
                if (j > i) f[i][j] = f[i][j-1];
                f[i][j] = max(f[i][j], f[i-1][j-1] * coins[j].c + coins[j].d);
            }
        }
        cout << (fixed) << setprecision(2) << f[k][n] << '\n';
    }
}
