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

const int INF = 1e18;
struct Test {
    Test(int _n) : n(_n), a(_n), prefix_sum(_n), cached(_n, vector<int> (_n, -1)) {
        cin >> x >> y;
        for (int& val : a) cin >> val;
        std::partial_sum(a.begin(), a.end(), prefix_sum.begin());
    }

    // Consider the game with only cells in [l, r]
    // What's the minimum amount of money the 1st player need to win?
    int dp(int l, int r) {
        if (l > r) return INF;  // empty array => cannot win
        if (cached[l][r] >= 0) return cached[l][r];

        int res = INF;

        // At this stage, we already bought all houses in [0, l-1] and [r+1, n-1]
        int totalMoneyLeft = x + y - get_sum(0, l-1) - get_sum(r+1, n-1);

        // Case 1: 1st player play L
        {
            int need = max(
                a[l],  // need to buy house at L
                totalMoneyLeft - dp(l+1, r) + 1  // make sure 2nd player doesn't have
                                                 // enough money to win
            );
            res = min(res, need);
        }
        // Case 2: 1st player play R
        {
            int need = max(
                a[r],
                totalMoneyLeft - dp(l, r-1) + 1
            );
            res = min(res, need);
        }

        return cached[l][r] = res;
    }

    string winner() {
        return x >= dp(0, n-1) ? "Haros" : "Iwys";
    }

    int get_sum(int l, int r) {  // [l, r]
        if (l > r) return 0;
        return l == 0 ? prefix_sum[r] : prefix_sum[r] - prefix_sum[l-1];
    }

    int n, x, y;
    vector<int> a, prefix_sum;
    vector<vector<int>> cached;
};

void solve() {
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        Test test(n);
        cout << test.winner() << '\n';
    }
}
