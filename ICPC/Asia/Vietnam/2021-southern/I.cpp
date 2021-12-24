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

const int MN = 1000111;
int bit[MN];

int get(int u) {
    int res = 0;
    for (; u > 0; u -= u & -u) {
        res += bit[u];
    }
    return res;
}

void update(int u, int val) {
    for (; u < MN; u += u & -u) {
        bit[u] += val;
    }
}

int res[MN];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<pair<int,int>> a(n+1);
    FOR(i,1,n) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin() + 1, a.end());

    int inversions = 0;
    FOR(i,1,n) {
        assert(a[i].first == i);
        int pos = a[i].second;
        res[i] = inversions;

        inversions += i - 1 - get(pos);
        update(pos, +1);
    }

    memset(bit, 0, sizeof bit);

    inversions = 0;
    FORD(i,n,1) {
        int pos = a[i].second;

        res[a[i].first] += inversions;

        inversions += get(pos);
        update(pos, +1);
    }

    cout << *min_element(res+1, res+n+1) << endl;

    return 0;
}
