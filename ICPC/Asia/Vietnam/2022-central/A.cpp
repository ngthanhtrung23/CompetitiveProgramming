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

int cache[311][311][311];
int a[311];
int n, k;
string s;

int f(int l, int r, int nBlack) {
    // wrong test data: total black < 2k+1
    if (l > r) return 1;

    if (cache[l][r][nBlack] >= 0) return cache[l][r][nBlack];
    int& res = cache[l][r][nBlack];

    // how many blacks the other player have taken
    int otherBlack = a[l-1] + (a[n] - a[r]) - nBlack;
    assert(nBlack + otherBlack + a[r] - a[l-1] == a[n]);

    // take s[l]
    if (s[l] == 'W' || (s[l] == 'B' && nBlack < k)) {
        if (f(l+1, r, otherBlack) == 0) {
            return res = 1;
        }
    }
    // take s[r]
    if (s[r] == 'W' || (s[r] == 'B' && nBlack < k)) {
        if (f(l, r-1, otherBlack) == 0) {
            return res = 1;
        }
    }

    return res = 0;
}

void solve() {
    cin >> n >> k;
    cin >> s;
    s = " " + s + " ";
    for (int i = 1; i <= n; ++i) {
        a[i] = a[i-1] + (s[i] == 'B' ? 1 : 0);
    }

    memset(cache, -1, sizeof cache);
    cout << (f(1, n, 0) ? "YES" : "NO") << endl;
    // wrong 2nd example, correct output is YES
}
