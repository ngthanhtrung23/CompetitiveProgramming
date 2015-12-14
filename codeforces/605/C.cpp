
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const double EPS = 1e-6;
const double INF = 1e9;

int cmp(double x, double y) {
    if (fabs(x - y) < EPS) return 0;
    if (x < y) return -1;
    return 1;
}

// ------------------------ BASIC TYPE
struct D {
    double x;

    D() {}
    D(double x) : x(x) {}

    D operator + (const D& a) const { return D(x+a.x); }
    D operator - (const D& a) const { return D(x-a.x); }
    D operator * (const D& a) const { return D(x*a.x); }
    D operator / (const D& a) const { return D(x/a.x); }

    D operator - () const { return D(-x); }

    D& operator += (const D& a) { return *this = *this + a; }
    D& operator -= (const D& a) { return *this = *this - a; }
    D& operator *= (const D& a) { return *this = *this * a; }
    D& operator /= (const D& a) { return *this = *this / a; }

    bool operator == (const D& a) const { return cmp(x, a.x) == 0; }
    bool operator <= (const D& a) const { return cmp(x, a.x) <= 0; }
    bool operator >= (const D& a) const { return cmp(x, a.x) >= 0; }
    bool operator <  (const D& a) const { return cmp(x, a.x) <  0; }
    bool operator >  (const D& a) const { return cmp(x, a.x) >  0; }
    bool operator != (const D& a) const { return cmp(x, a.x) != 0; }

    int sign() {
        int t = cmp(x, 0);
        if (t == 0) return 0;
        if (t < 0) return -1;
        return 1;
    }

    friend istream& operator >> (istream& cin, D& x) {
        cin >> x.x;
        return cin;
    }
    friend ostream& operator << (ostream& cout, D& x) {
        cout << x.x;
        return cout;
    }
} O(0.0), PI(acos((double) -1.0));

int cmp(const D& a, const D& b) {
    return cmp(a.x, b.x);
}

D sqrt(D x) { assert(x >= 0); return D(sqrt(x.x)); }
D abs(D x) { if (x < 0) return -x; else return x; }
D fabs(D x) { if (x < 0) return -x; else return x; }
D sin(D x) { return sin(x.x); }
D cos(D x) { return cos(x.x); }
D tan(D x) { return tan(x.x); }
D asin(D x) { assert(D(-1) <= x && x <= D(1)); return asin(x.x); }
D acos(D x) { assert(D(-1) <= x && x <= D(1)); return acos(x.x); }
D atan(D x) { return atan(x.x); }

struct Point {
    D x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point(D x, D y) : x(x), y(y) {}

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator * (const D& k)     const { return Point(x*k, y*k); }
    Point operator / (const D& k)     const { assert(k != D(0)); return Point(x/k, y/k); }

    D operator * (const Point& a)     const { return x*a.x + y*a.y; } // dot
    D operator % (const Point& a)     const { return x*a.y - y*a.x; } // cross

    friend istream& operator >> (istream& cin, Point& a) {
        cin >> a.x >> a.y;
        return cin;
    }
    friend ostream& operator << (ostream& cout, Point& a) {
        cout << a.x << ' ' << a.y;
        return cout;
    }

    D norm() { return x*x + y*y; }
    D len() { return hypot(x.x, y.x); }

    Point rotate(D alpha) {
        D cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }

    Point normalize(D l) {
        return Point(x, y) * l / len();
    }
};
D angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}
int ccw(const Point& a, const Point& b, const Point& c) {
    return ((b - a) % (c - a)).sign();
}

struct Line {
    D a, b, c;
    Point A, B;

    Line(D a, D b, D c) : a(a), b(b), c(c) {}

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = D(0) - (a * A.x + b * A.y);
    }
    D f(const Point &p) {
        return a*p.x + b*p.y + c;
    }

    D dist(Point p) {
        return fabs(a*p.x + b*p.y + c) / sqrt(a*a + b*b);
    }
};

// ------------------------ Line operations
bool areParallel(Line l1, Line l2) {
    return l1.a*l2.b == l1.b*l2.a;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1 ,l2) && l1.c*l2.a == l2.c*l1.a
            && l1.c*l2.b == l1.b*l2.c;
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    D dx = l1.b*l2.c - l2.b*l1.c;
    D dy = l1.c*l2.a - l2.c*l1.a;
    D d    = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

// ------------------------ Polygon
typedef vector< Point > Polygon;

D area2(Point a, Point b, Point c) { return a%b + b%c + c%a; }
bool between(const Point &a, const Point &b, const Point &c) {
    return (fabs(area2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
void ConvexHull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<Point> up, dn;
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
    
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < pts.size(); i++) {
        if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
}

int n;

bool order(Point a, Point b, Point c) {
    return min(a, c) <= b && b <= max(a, c);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    Point P;
    while (cin >> n >> P) {
        Polygon a;
        D max_x = -1, max_y = -1;
        FOR(i,1,n) {
            Point t; cin >> t;
            a.push_back(t);
            max_x = max(max_x, t.x);
            max_y = max(max_y, t.y);
        }
        a.push_back(Point(0, 0));
        a.push_back(Point(0, max_y));
        a.push_back(Point(max_x, 0));
        ConvexHull(a);
//        for(auto p : a) cout << p.x << ' ' << p.y << endl;
//        cout << endl;

        Line OP(Point(O, O), P);
        D best = O;
        REP(i,SZ(a)) {
            int j = (i + 1) % SZ(a);
            Line ij = Line(a[i], a[j]);

            Point t;
            if (areIntersect(OP, ij, t) && order(a[i], t, a[j])) {
//                DEBUG(t);
                best = max(best, t.len());
            }
        }
        D res = P.len() / best;
        cout << res << endl;
    }
}
