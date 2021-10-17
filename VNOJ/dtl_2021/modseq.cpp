// brute force, for small subtask.

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
template<class U, class V> ostream& operator << (ostream& cout, const pair<U, V>& p) {
    return cout << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator << (ostream& cout, const Con& con) {
    cout << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        cout << (it == beg ? "" : ", ") << *it;
    }
    return cout << '}';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& cout, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return cout << ")"; 
    else return print_tuple_utils<i + 1, T>(cout << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& cout, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(cout, t);
}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

int power(int x, int k, int mod) {
    if (k == 0) return 1 % mod;

    int res = 1 % mod;
    while (k > 0) {
        if (k & 1) res = (res * x) % mod;
        k >>= 1;
        x = x * x % mod;
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int a, m; cin >> a >> m;
    FOR(x,1,1000111) {
        if (power(a, x, m) == x % m) {
            cout << x << endl;
            return 0;
            cout << x << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
