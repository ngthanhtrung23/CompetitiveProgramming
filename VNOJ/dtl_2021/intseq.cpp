#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

int f[10111];
int updated[10111];
vector< pair<int,int> > edges[10111];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;

    // s: suffix sum
    while (k--) {
        int l, r, x, y; cin >> l >> r >> x >> y;

        // x <= s[l] - s[r+1] <= y
        //
        // s[l] <= s[r+1] + y
        // s[r+1] <= s[l] - x

        edges[l].push_back({r+1, y});
        edges[r+1].push_back({l, -x});
    }

    FOR(i,1,n) {
        // a[i] >= 0
        // s[i] - s[i+1] >= 0
        // s[i+1] <= s[i]

        edges[i+1].push_back({i, 0});
    }

    const int INF = 1e18;
    FOR(i,1,n+1) {
        f[i] = (i == n+1) ? 0 : INF;
    }

    const int LIMIT = 100;
    queue<int> qu;
    qu.push(n+1);
    try {
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();

            for (auto [v, cost] : edges[u]) {
                if (f[v] > f[u] + cost) {
                    f[v] = f[u] + cost;
                    qu.push(v);
                    ++updated[u];
                    if (updated[v] > LIMIT) throw 1;
                }
            }
        }

        FOR(i,1,n) {
            cout << f[i+1] - f[i] << ' ';
        }
        cout << endl;
    } catch (...) {
        // negative cycle -> unbounded
        cout << -1 << endl;
        return 0;
    }

    return 0;
}
