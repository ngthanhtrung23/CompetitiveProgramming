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

const double PI = acos(-1.0);

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

// for int types
template<typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type * = nullptr>
inline int cmp(T a, T b) {
    return (a == b) ? 0 : (a < b) ? -1 : 1;
}

template<typename T>
struct P {
    T x, y;
    P() { x = y = T(0); }
    P(T _x, T _y) : x(_x), y(_y) {}

    P operator + (const P& a) const { return P(x+a.x, y+a.y); }
    P operator - (const P& a) const { return P(x-a.x, y-a.y); }
    P operator * (T k) const { return P(x*k, y*k); }
    P<double> operator / (double k) const { return P(x/k, y/k); }

    T operator * (const P& a) const { return x*a.x + y*a.y; } // dot product
    T operator % (const P& a) const { return x*a.y - y*a.x; } // cross product

    int cmp(const P<T>& q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (const P& q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    T sqlen() { return x*x + y*y; }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(sqlen()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return hypot(x, y); }

    P<double> rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return P(x * cosa - y * sina, x * sina + y * cosa);
    }
};
template<typename T>
istream& operator >> (istream& cin, P<T>& p) {
    cin >> p.x >> p.y;
    return cin;
}
template<typename T>
ostream& operator << (ostream& cout, const P<T>& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}

template<typename T>
int ccw(P<T> a, P<T> b, P<T> c) {
    return cmp((b-a)%(c-a), T(0));
}

template<typename T>
bool onSegment(const P<T>& a, const P<T>& b, const P<T>& p) {
    return ccw(a, b, p) == 0
        && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)
        && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

#define REMOVE_REDUNDANT
template<typename T>
T area2(P<T> a, P<T> b, P<T> c) { return a%b + b%c + c%a; }

template<typename T>
void ConvexHull(vector<P<T>> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<P<T>> up, dn;
    for (int i = 0; i < (int) pts.size(); i++) {
#ifdef REMOVE_REDUNDANT
        while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
#else
        while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) > 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) < 0) dn.pop_back();
#endif
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
    
#ifdef REMOVE_REDUNDANT
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < (int) pts.size(); i++) {
        if (onSegment(dn[dn.size()-2], pts[i], dn.back())) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && onSegment(dn.back(), dn[1], dn[0])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
#endif
}
using Point = P<int>;
const int INF = 1e18;

void solve() {
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n, k, d; cin >> n >> k >> d;
        vector<Point> a(n);
        for(auto& p : a) cin >> p;
        ConvexHull(a);
        sort(a.begin(), a.end());
        n = SZ(a);
        DEBUG(n);

        vector<int> f(n, INF);
        f[0] = 0;
        auto update = [&] (int j, int i) {
            auto sqdist = (a[j] - a[i]).sqlen();
            if (sqdist <= d*d) {
                f[i] = min(f[i], f[j] + max(k, sqdist));
            }
        };

        vector<bool> fixed(n, false);
        // N^2 dijkstra
        REP(turn,n) {
            // best = current shortest vertex
            int best = -1;
            REP(i,n) if (!fixed[i]) {
                if (best < 0 || f[i] < f[best]) best = i;
            }
            assert(best >= 0);
            fixed[best] = true;

            // update distances of all vertices
            REP(i,n) {
                if (fixed[i]) continue;

                update(best, i);
            }
        }
        if (f.back() == INF) f.back() = -1;
        cout << "Case #" << test << ": " << f.back() << endl;
    }
}
