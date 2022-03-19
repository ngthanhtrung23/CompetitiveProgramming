#include "bits/stdc++.h"
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx2,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

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

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int r) {
    return uniform_int_distribution<int> (0, r-1)(rng);
}

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

vector< pair<int,int> > teles[300];
const vector< pair<int, int> > DIRS = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n_row, n_col; cin >> n_row >> n_col;
    vector<vector<int>> a(n_row, vector<int> (n_col, 0));
    vector<vector<int>> dist(n_row, vector<int> (n_col, -1));

    REP(i,n_row) REP(j,n_col) {
        cin >> a[i][j];
        if (a[i][j] > 0) {
            teles[a[i][j]].push_back({i, j});
        }
    }

    deque< pair<int,int> > qu;
    qu.push_back({0, 0});
    dist[0][0] = 0;

    while (!qu.empty()) {
        auto [u, v] = qu.front(); qu.pop_front();
        if (u == n_row - 1 && v == n_col - 1) {
            cout << dist[u][v] << endl;
            return 0;
        }

        // teleport
        for (auto [uu, vv] : teles[a[u][v]]) {
            if (dist[uu][vv] < 0) {
                dist[uu][vv] = dist[u][v];
                qu.push_front({uu, vv});
            }
        }

        // move
        for (auto [di, dj] : DIRS) {
            int uu = u + di, vv = v + dj;
            if (uu < 0 || uu >= n_row) continue;
            if (vv < 0 || vv >= n_col) continue;

            if (dist[uu][vv] >= 0) continue;

            dist[uu][vv] = dist[u][v] + 1;
            qu.push_back({uu, vv});
        }
    }

    assert(false);
    return 0;
}
