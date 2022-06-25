// Statements:
// - n students <= 10
// - t round    <= 100
//   - each round, each student eats 0 -> l <= 1000
//   --> in total, each student eats <= 10^5
// - diff (max - min) <= delta <= 10^6
// - initially: p1, ..., pn <= 10^7
//
//
// Idea:
// - nn = min. amount of squid
// --> nn -> nn+delta
// --> product( fi(nn+delta) - fi(nn-1) )
//     - product( fi(nn+delta) - fi(nn) )
//
// - for each student, fi(x) = no. ways student i eat == x squids

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

const int MOD = 998244353;

int g[111][200111], f[1100111];

int add(int a, int b) {
    return (a + b) % MOD;
}
int sub(int a, int b) {
    return (a - b + MOD) % MOD;
}

int count(const vector<int>& ps, int l, int r) {
    int res = 1;
    for (int p : ps) {
        if (p > r) {
            return 0;
        }

        // [l - p, r - p]
        int ll = max(l - p, 0LL);
        int rr = r - p;

        int cur = f[rr];
        if (ll > 0) cur = sub(cur, f[ll - 1]);

        res = (res * cur) % MOD;
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    int nStudent, maxEachRound, nRound, delta;
    cin >> nStudent >> maxEachRound >> nRound >> delta;
    vector<int> initials(nStudent);
    for (int& x : initials) cin >> x;

    // sort initials & check no solution
    sort(initials.begin(), initials.end());
    int nn = initials[0];
    for (int& x : initials) x -= nn;

    // init f
    FOR(x,0,100000) g[0][x] = 1;

    FOR(r,1,nRound) {
        FOR(x,0,r*maxEachRound) {
            // g[r][x] = sum(g[r-1][i], i = x - maxEachRound .. x)
            g[r][x] = sub(g[r-1][x], g[r-1][x - maxEachRound - 1]);
        }
        // accumulate g[r]
        FOR(x,1,100000) {
            g[r][x] = add(g[r][x], g[r][x-1]);
        }

        // PR0(g[r], r*maxEachRound + 1);
    }
    FOR(x,0,1100000) {
        if (x <= nRound*maxEachRound) {
            f[x] = g[nRound][x];
        } else {
            f[x] = g[nRound][nRound*maxEachRound];
        }
    }
    // PR0(f, nRound*maxEachRound + 1);

    // find result
    // p = 0, p1 - p0, p2 - p0, ....
    int res = 0;
    // PR0(initials, nStudent);
    FOR(l,0,nRound*maxEachRound) {  // 10^5
        int r = l + delta;
        // count no. ways:
        // - at least 1 student eat == l
        // - all students eat [l, r]

        int cur = sub(count(initials, l, r), count(initials, l + 1, r));
        // cout << l << ' ' << r << ' ' << cur << endl;
        // DEBUG(count(initials, l, r));
        // DEBUG(count(initials, l+1, r));
        res = add(res, cur);
    }
    cout << res << endl;
    return 0;
}
