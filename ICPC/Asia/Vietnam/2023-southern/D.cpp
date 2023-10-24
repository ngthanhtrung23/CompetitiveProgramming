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

const int INF = 1000111000;
const std::vector<std::pair<int,int>> DIRECTIONS = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
};
int min_danger(const vector<vector<int>>& a, int weight) {
    int n = a.size();
    deque<pair<int,int>> qu;
    vector<vector<int>> f(n, vector<int> (n, -1));
    qu.push_front({0, 0});
    f[0][0] = a[0][0] < weight;

    while (!qu.empty()) {
        auto [u, v] = qu.front(); qu.pop_front();
        if (u == n-1 && v == n-1) return f[u][v];
        for (auto [du, dv] : DIRECTIONS) {
            int uu = u + du, vv = v + dv;
            if (uu < 0 || uu >= n) continue;
            if (vv < 0 || vv >= n) continue;
            if (f[uu][vv] >= 0) continue;

            if (a[uu][vv] >= weight) {
                qu.push_front({uu, vv});
                f[uu][vv] = f[u][v];
            } else {
                qu.push_back({uu, vv});
                f[uu][vv] = f[u][v] + 1;
            }
        }
    }
    return INF;
}

void solve() {
    int typ, n; cin >> typ >> n;
    int weight = 0;
    if (typ == 1) cin >> weight;
    vector<vector<int>> a(n, vector<int> (n));
    for (auto& row : a) for (auto& x : row) cin >> x;

    if (typ == 1) {
        cout << min_danger(a, weight) << endl;
    } else {
        int l = 1, r = 10000, res = 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (min_danger(a, mid) == 0) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << res << endl;
    }
}
