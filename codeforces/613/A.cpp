
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

// Distance from p to Line ab (closest Point --> c)
D distToLine(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    D u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p-c).len();
}

// Distance from p to segment ab (closest Point --> c)
D distToLineSegment(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    D u = (ap * ab) / ab.norm();
    if (u < O) {
        c = Point(a.x, a.y);
        return (p - a).len();
    }
    if (u > D(1.0)) {
        c = Point(b.x, b.y);
        return (p - b).len();
    }
    return distToLine(p, a, b, c);
}

const int MN = 100111;
int n;
Point a[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    Point P;
    while (cin >> n >> P) {
        D nn = INF, ln = -INF;
        Point tmp;
        FOR(i,1,n) {
            cin >> a[i];

            nn = min(nn, (a[i] - P).len());
            ln = max(ln, (a[i] - P).len());
        }
        a[n+1] = a[1];
        FOR(i,1,n) {
            nn = min(nn, distToLineSegment(P, a[i], a[i+1], tmp));
        }
        D res = PI * (ln*ln - nn*nn);
        cout << res << endl;
    }
}
