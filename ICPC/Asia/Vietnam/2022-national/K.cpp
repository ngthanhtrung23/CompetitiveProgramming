// template {{{
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
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
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
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
    solve();
    return 0;
}

// }}}
// Point {{{
struct Point {
    int x, y;

    Point() {}
    Point(int x_, int y_) : x(x_), y(y_) {}

    Point operator + (const Point& a) {
        return Point {x + a.x, y + a.y};
    }
    Point operator - (const Point& a) {
        return Point {x - a.x, y - a.y};
    }
    
    int sign() const {
        if (x == 0 && y == 0) return 0;
        if (y < 0 || (y == 0 && x > 0)) return -1;
        return 1;
    }
};
bool operator < (const Point& a, const Point& b) {
    if (a.sign() != b.sign()) return a.sign() < b.sign();
    return a.x*b.y > b.x*a.y;
}
bool operator == (const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}
ostream& operator << (ostream& cout, const Point& p) {
    return cout << p.x << ' ' << p.y;
}
bool operator != (const Point& a, const Point& b) {
    return !(a == b);
}
// }}}

vector< Point > genPrimitivePytTriples(int n) {
    vector< Point > res;
    res.emplace_back(3, 0);
    for (int r=1; r*r<=n; ++r) for (int s=(r%2==0)?1:2; s<r; s+=2) if (__gcd(r,s)==1) {
        int x = r*r - s*s;
        int y = 2*r*s;
        if (x <= n && y <= n) {
            res.push_back({x, y});
            res.push_back({y, x});
        }
    }
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

void solve() {
    const int MAXV = 4000;
    auto vs = genPrimitivePytTriples(MAXV);
    int n; cin >> n;

    assert(SZ(vs) >= n/2 - 1 + n % 2);

    vs.resize(n/2 - 1 + n % 2);
    vs.emplace_back(0, 4);
    reverse(vs.begin(), vs.end());

    Point orig {-1000000, -1000000};
    if (n % 2 == 0) {
        Point cur = orig;
        cout << "YES" << endl;
        REP(i,n/2) {
            cout << cur << '\n';
            assert(abs(cur.x) <= 1000000 && abs(cur.y) <= 1000000);
            cur = cur + vs[i];
        }
        REP(i,n/2) {
            cout << cur << '\n';
            assert(abs(cur.x) <= 1000000 && abs(cur.y) <= 1000000);
            cur = cur - vs[i];
        }
    } else {
        ++n;

        Point cur = orig;
        cout << "YES" << endl;
        REP(i,n/2) {
            if (cur != orig) cout << cur << '\n';
            assert(abs(cur.x) <= 1000000 && abs(cur.y) <= 1000000);
            cur = cur + vs[i];
        }
        REP(i,n/2) {
            if (cur != orig) cout << cur << '\n';
            assert(cur.x <= 1000000 && cur.y <= 1000000);
            cur = cur - vs[i];
        }
    }
}
