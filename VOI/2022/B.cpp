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
long long get_rand(long long r) {  // [0, r)
    return uniform_int_distribution<long long> (0, r-1)(rng);
}
long long get_rand(long long l, long long r) {  // [l, r]
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

const int MOD = 1e9 + 7;

// f[i][positives] = so day i..n-1
//                   positives = so so > 0 tu i..n
int f[2011][2011];
inline int add(int a, int b) {
    return (a + b) % MOD;
}

void solve() {
#ifndef RR
    freopen("GRAPH.INP", "r", stdin);
    freopen("GRAPH.OUT", "w", stdout);
#endif

    int n, b; cin >> n >> b;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    f[n][0] = 1;
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j <= n - i; ++j) {
            if (a[i] < 0) {
                // set a[i] = 0
                if (j <= b) {
                    f[i][j] = f[i+1][j];
                }

                // set a[i] > 0
                // a[i] + (j-1) <= b
                // a[i] <= b - j + 1
                int bound = min(b - j + 1, i);
                if (bound >= 1) {
                    f[i][j] = add(f[i][j], f[i+1][j-1] * bound);
                }
            } else {
                // a[i] + positive[i+1] <= b
                // positive[i+1] <= b - a[i]
                int can = b - a[i];

                // a[i] is known
                if (a[i] > 0) {
                    if (j > 0 && j-1 <= can) {
                        f[i][j] = f[i+1][j-1];
                    }
                } else {
                    if (j <= can) {
                        f[i][j] = f[i+1][j];
                    }
                }
            }
        }
    }

    int sum = 0;
    for (int p = 0; p <= n; ++p) sum = add(sum, f[0][p]);
    cout << sum << endl;
}
