// template {{{
// CF pragma: https://codeforces.com/blog/entry/96344
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#ifndef UNSAFE_NO_DEFINE_INT_LONG_LONG
#define int long long
#endif
#define I(x) int x; cin >> x;
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define FORD(i,a,b) for(int i=(a),_##i##_b=(b); i>=_##i##_b; i--)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))

// For printing pair, container, etc.
// Copied from https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
template<class U, class V> ostream& operator << (ostream& out, const pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if (i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> ostream& operator << (ostream& out, const tuple<U...>& t) {
    return print_tuple_utils<0, tuple<U...>>(out, t);
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_rand(long long r) {  // [0, r)
    return uniform_int_distribution<long long> (0, r-1)(rng);
}
long long get_rand(long long l, long long r) {  // [l, r]
    return uniform_int_distribution<long long> (l, r)(rng);
}

template<typename T>
vector<T> read_vector(int n) {
    vector<T> res(n);
    for (auto& x : res) cin >> x;
    return res;
}

void solve();

template<typename T> void upMin(T& x, T val) { if (val < x) x = val; }
template<typename T> void upMax(T& x, T val) { if (val > x) x = val; }

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}

// }}}

struct Point {
    int x, y;

    Point operator - (const Point& a) const {
        return Point{ x - a.x, y - a.y };
    }
    int operator % (const Point& a) const {
        return x*a.y - y*a.x;
    }
};
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream& operator << (ostream& cout, const Point& p) {
    cout << '(' << p.x << ' ' << p.y << ')';
    return cout;
}
using Polygon = vector<Point>;

int signed_area2(const Polygon& p) {
    int n = p.size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res += p[i] % p[(i+1) % n];
    }
    return res;
}

int area2(const Polygon& p) {
    return abs(signed_area2(p));
}

bool inside(const Point& p, const Polygon& poly) {
    int s = 0;
    int n = SZ(poly);

    REP(i,n) {
        s += area2({p, poly[i], poly[(i+1) % n]});
    }

    return s == area2(poly);
}

void solve() {
#ifndef RR
    freopen("PAINT.INP", "r", stdin);
    freopen("PAINT.OUT", "w", stdout);
#endif
    int W, H; cin >> W >> H;
    int n; cin >> n;
    vector<Polygon> polys(n);

    int m; cin >> m;
    int q; cin >> q;

    REP(i,n) {
        polys[i].resize(m);
        REP(j,m) cin >> polys[i][j];
    }

    polys.push_back({
        {0, 0},
        {W, 0},
        {W, H},
        {0, H},
    });

    sort(polys.begin(), polys.end(), [&] (const Polygon& a, const Polygon& b) {
        return area2(a) < area2(b);
    });

    n = SZ(polys);

    vector<int> areas(n);
    REP(i,n) {
        areas[i] = area2(polys[i]);
    }

    FORD(i,n-1,0) {
        Point p = polys[i][0];
        FOR(j,i+1,n-1) {
            if (inside(p, polys[j])) {
                areas[j] -= areas[i];
                break;
            }
        }
    }

    cout << (fixed) << setprecision(1);
    while (q--) {
        Point p; cin >> p;
        REP(i,n) {
            if (inside(p, polys[i])) {
                cout << areas[i] / 2.0 << '\n';
                break;
            }
        }
    }
}
