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

const int INF = 1000111000111000111LL;
vector<vector<int>> dp(2011, vector<int> (2011, -1));
int f(int cur_sum, int rem_open) {
    if (cur_sum == 0 && rem_open == 0) return 1;
    int& res = dp[cur_sum][rem_open];
    if (res >= 0) return res;

    res = 0;
    if (rem_open > 0) res += f(cur_sum + 1, rem_open - 1);
    if (cur_sum > 0) res += f(cur_sum - 1, rem_open);
    if (res >= INF) res = INF;
    return res;
}

void solve1() {
    int n, k; cin >> n >> k;
    vector<int> res(2*n);
    int sum = 0, opened = 0, closed = 0;
    for (int i = 0; i < 2*n; ++i) {
        if (opened < n && f(sum+1, n-opened-1) >= k) {
            res[opened] = i+1;
            ++opened;
            ++sum;
        } else {
            if (sum == 0) {
                DEBUG(i);
                DEBUG(res);
                DEBUG(f(sum+1, n-opened-1));
                DEBUG(k);
            }
            if (opened < n) k -= f(sum+1, n-opened-1);
            res[n + closed] = i+1;
            ++closed;
            --sum;
            assert(sum >= 0);
        }
    }
    for (int r : res) cout << r << ' '; cout << endl;
}

void solve2() {
    int n; cin >> n;
    vector<int> a(2*n); for (int& x : a) cin >> x;
    int res = 0;

    int pos = 1, sum = 0, opened = 0;
    for (int i = 0; i < n; ++i) {
        while (a[i] > pos) {
            // this position is )
            // greater than if we put ( here
            res += f(sum + 1, n - opened - 1);
            ++pos;
            --sum;
        }
        ++opened;
        ++sum;
        ++pos;
    }
    cout << res + 1 << endl;
}

void solve() {
    int typ;
    while (cin >> typ) {
        if (typ == 1) solve1();
        else solve2();
    }
}

/*
 * n = 3
 * 1 2 3 4 5 6
 * ( ( ( ) ) )
 *
 * 1 2 4 3 5 6
 * ( ( ) ( ) )
 *
 * 1 2 5 3 4 6
 * ( ( ) ) ( )
 *
 * 1 3 4 2 5 6
 * ( ) ( ( ) )
 *
 * 1 3 5 2 4 6
 * ( ) ( ) ( )
 */
