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

int cache[111][20111];
int n;
const int INF = 1e18 + 11;

int dp(int i, int inversions) {
    if (i == n) return inversions == 0 ? 1 : 0;
    if (cache[i][inversions] >= 0) return cache[i][inversions];

    int res = 0;
    for (int cur = 0; cur <= n-i-1; cur++) {
        if (inversions >= cur) {
            res += dp(i+1, inversions - cur);
            if (res >= INF) res = INF;
        }
    }

    return cache[i][inversions] = res;
}

void solve() {
    int m, k; cin >> n >> m >> k;

    memset(cache, -1, sizeof cache);
    if (dp(0, m) < k) {
        cout << -1 << endl;
        return;
    }

    vector<int> remaining_digits(n);
    std::iota(remaining_digits.begin(), remaining_digits.end(), 0);
    vector<int> res;

    for (int i = 0; i < n; ++i) {
        int cnt_lower = 0;
        for (int j = 0; j < SZ(remaining_digits); ++j) {
            int cur = dp(i+1, m - j);
            if (cnt_lower + cur >= k) {
                res.push_back(remaining_digits[j]);
                remaining_digits.erase(remaining_digits.begin() + j);
                k -= cnt_lower;
                m -= j;
                break;
            }
            cnt_lower += cur;
        }
    }

    for (int r : res) cout << r+1 << ' ';
    cout << endl;
}
