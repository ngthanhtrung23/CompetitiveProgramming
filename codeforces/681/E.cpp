#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}
void GN(double& x) {
    int t; GI(t);
    x = t;
}

#define EPS 1e-6
const double PI = acos(-1.0);

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator * (double k) const { return Point(x*k, y*k); }
    Point operator / (double k) const { return Point(x/k, y/k); }

    double operator * (const Point& a) const { return x*a.x + y*a.y; } // dot product
    double operator % (const Point& a) const { return x*a.y - y*a.x; } // cross product

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    Point conj() { return Point(x, -y); }
    double norm() { return x*x + y*y; }

    Point normalizeTo(double len) {
        return Point(x, y) / norm() * len;
    }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return sqrt(norm()); }

    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}
struct Circle : Point {
    double r;
    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}
    Circle(Point p, double r) : Point(p), r(r) {}
    
    bool contains(Point p) { return (*this - p).len() <= r + EPS; }
};
bool areIntersect(Circle u, Circle v) {
    if (cmp((u - v).len(), u.r + v.r) > 0) return false;
    if (cmp((u - v).len() + v.r, u.r) < 0) return false;
    if (cmp((u - v).len() + u.r, v.r) < 0) return false;
    return true;
}
vector<Point> circleIntersect(Circle u, Circle v) {
    vector<Point> res;
    if (!areIntersect(u, v)) return res;
    double d = (u - v).len();
    double alpha = acos((u.r * u.r + d*d - v.r * v.r) / 2.0 / u.r / d);

    Point p1 = (v - u).rotate(alpha);
    Point p2 = (v - u).rotate(-alpha);
    res.push_back(p1 / p1.len() * u.r + u);
    res.push_back(p2 / p2.len() * u.r + u);
    return res;
}

const int MN = 200111;
Circle a[MN];
int n;
Point start;
double R;

double segment_union(vector< pair<double, double> > segs) {
    int n = SZ(segs);
    vector< pair<double, bool> > x(n*2);
    REP(i,n) {
        x[i*2] = make_pair(segs[i].first, false);
        x[i*2+1] = make_pair(segs[i].second, true);
    }
    sort(x.begin(), x.end());

    double res = 0.0;
    int c = 0;
    REP(i,n*2) {
        if (c && i) res += x[i].first - x[i-1].first;
        if (x[i].second) ++c;
        else --c;
    }
    return res;
}

double directed_angle(Point a, Point o, Point b) { // angle AOB, in range [0, 2*PI)
    double t = -atan2(a.y - o.y, a.x - o.x)
            + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2*PI;
    return t;
}

double range(double l, double r) {
    if (l < r) return r - l;
    else return r - l + 2 * PI;
}

void solve() {
    FOR(i,1,n) if (sqr(a[i].x) + sqr(a[i].y) < sqr(a[i].r) + 1e-10) {
        cout << 1.0 << endl;
        return ;
    }
    Circle C;
    C.x = start.x; C.y = start.y; C.r = R;

    Point hor(1, 0);

    vector< pair<double,double> > segs;
    FOR(i,1,n) {
        auto t = circleIntersect(C, a[i]);
        double a1, a2;

        if (C.contains(a[i])) {
            double mid = atan2(a[i].x, a[i].y);
            double half = asin(a[i].r / a[i].len());

            a1 = mid - half;
            a2 = mid + half;
        }
        else if (SZ(t) == 2) {
            auto u = t[0];
            auto v = t[1];

            a1 = atan2(u.x, u.y);
            a2 = atan2(v.x, v.y);
        }
        else continue;

        while (a1 < 0) a1 += 2 * PI;
        while (a2 < 0) a2 += 2 * PI;
        while (a1 > 2*PI) a1 -= 2*PI;
        while (a2 > 2*PI) a2 -= 2*PI;
        if (fabs(a1 - a2) < 1e-10) continue;

        if (range(a1, a2) > PI) swap(a1, a2);

        if (a1 <= a2) {
            segs.emplace_back(a1, a2);
        }
        else {
            segs.emplace_back(a1, 2*PI);
            segs.emplace_back(0, a2);
        }
    }
    double sum = segment_union(segs);

    cout << sum / (double) (2*PI) << endl;
}

#undef int
int main() {
#define int long long
    cout << (fixed) << setprecision(14);
    double v, T;
    GN(start.x);
    GN(start.y);
    GN(v);
    GN(T);

    R = v * T;
    GI(n);
    FOR(i,1,n) {
        GN(a[i].x);
        GN(a[i].y);
        GN(a[i].r);
        a[i].x -= start.x;
        a[i].y -= start.y;
    }
    start = Point(0, 0);

    solve();
}
