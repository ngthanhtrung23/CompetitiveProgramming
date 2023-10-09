// template {{{
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define REP(i,a) for(int i=0,_##i##_a=(a); i<_##i##_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define SZ(s) ((int) ((s).size()))
#define sqr(x) ((x) * (x))

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

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}
// }}}

struct Point {
    int x, y, z;
    
    Point() { x = y = z = 0; }
    Point(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

    double len() {
        return sqrt(x * (double) x + y * y + z * z);
    }
    Point operator - (Point a) { return Point(x-a.x, y-a.y, z-a.z); }
};
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y >> p.z;
    return cin;
}

vector<pair<Point, string>> COLORS {
    {{255, 255, 255}, "White"},
    {{192, 192, 192}, "Silver"},
    {{128, 128, 128}, "Gray"},
    {{0, 0, 0}, "Black"},
    {{255, 0, 0}, "Red"},
    {{128, 0, 0}, "Maroon"},
    {{255, 255, 0}, "Yellow"},
    {{128, 128, 0}, "Olive"},
    {{0, 255, 0}, "Lime"},
    {{0, 128, 0}, "Green"},
    {{0, 255, 255}, "Aqua"},
    {{0, 128, 128}, "Teal"},
    {{0, 0, 255}, "Blue"},
    {{0, 0, 128}, "Navy"},
    {{255, 0, 255}, "Fuchsia"},
    {{128, 0, 128}, "Purple"},
};

void solve() {
    Point p;
    while (cin >> p) {
        if (p.x < 0) break;

        double min_dist = 1e10;
        string res = "";

        for (const auto& [p2, name] : COLORS) {
            double dist = (p - p2).len();
            if (dist < min_dist) {
                min_dist = dist;
                res = name;
            }
        }
        cout << res << '\n';
    }
}
