#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

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

int f[5011][5011];
int a[5011];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);

    memset(f, -1, sizeof f);

    queue<pair<int,int>> qu;
    qu.push({0, 0});
    f[0][0] = 0;

    queue<pair<int,int>> next_qu;
    auto go = [&](int w1, int w2, int cur_f) {
        if (w1 > 5000 || w2 > 5000) return;
        if (f[w1][w2] >= 0) return;

        f[w1][w2] = cur_f + 1;
        next_qu.push({w1, w2});
    };

    FOR(i,1,n) {
        while (!qu.empty()) {
            auto [w1, w2] = qu.front(); qu.pop();
            go(w1 + a[i], w2, f[w1][w2]);
            go(w1, w2 + a[i], f[w1][w2]);
        }

        qu = std::move(next_qu);
    }

    long long res = 0;
    FOR(i,1,5000) FOR(j,1,5000) {
        f[i][j] = max(f[i][j], max(f[i-1][j], f[i][j-1]));
        if (f[i][j] < 0) f[i][j] = 0;
        res += i ^ j ^ f[i][j];
    }
    cout << res << endl;
    return 0;
}
