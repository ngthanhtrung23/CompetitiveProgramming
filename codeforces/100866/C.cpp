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
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

#define EPS 1e-10
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

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return hypot(x, y); }

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
struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double a, double b, double c) : a(a), b(b), c(c) {} 

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
    Line(Point P, double m) {
        a = -m; b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point A) {
        return a*A.x + b*A.y + c;
    }
};

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a*l2.b, l1.b*l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1 ,l2) && cmp(l1.c*l2.a, l2.c*l1.a) == 0
                && cmp(l1.c*l2.b, l1.b*l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d  = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

double X1, X2, Y1, Y2;
int n;
Point p[511], v[511];

bool outside(Point p) {
    return cmp(p.x, X1) < 0
        || cmp(p.y, Y1) < 0
        || cmp(p.x, X2) > 0
        || cmp(p.y, Y2) > 0;
}
bool order(Point a, Point b, Point c) {
    return cmp(min(a.x, c.x), b.x) <= 0
        && cmp(max(a.x, c.x), b.x) >= 0
        && cmp(min(a.y, c.y), b.y) <= 0
        && cmp(max(a.y, c.y), b.y) >= 0;
}

double l[511], r[511];

double f(int i, int j, double t) {
    Point a = p[i] + v[i] * t;
    Point b = p[j] + v[j] * t;
    return (a - b).len();
}

double distToLine(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p-c).len();
}
double distToLineSegment(Point p, Point a, Point b, Point &c) {
    if (a == b) return (p - a).len();

    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    if (cmp(u, 0.0) < 0) {
        c = Point(a.x, a.y);
        return (p - a).len();
    }
    if (cmp(u, 1.0) > 0) {
        c = Point(b.x, b.y);
        return (p - b).len();
    }
    return distToLine(p, a, b, c);
}

double get(int i, int j) {
    double left = max(l[i], l[j]);
    double right = min(r[i], r[j]);
    if (left > right + EPS) return 1e100;

    Point Ai = p[i] + v[i] * left;
    Point Bi = p[i] + v[i] * right;

    Point Aj = p[j] + v[j] * left;
    Point Bj = p[j] + v[j] * right;

    Point tmp;
    return distToLineSegment(Point(0, 0), Aj - Ai, Bj - Bi, tmp);
}

void update(Line AB, Point A, Point B, Line t, int i) {
    Point X;
    if (areIntersect(AB, t, X)) {
        if (order(A, X, B)) {
            Point q = p[i] + v[i];
            if (order(X, p[i], q)) return;

            double time = (X - p[i]).len() / v[i].len();
            l[i] = min(l[i], time);
            r[i] = max(r[i], time);
        }
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(12);
    while (cin >> X1 >> Y1 >> X2 >> Y2) {
        if (X1 > X2) swap(X1, X2);
        if (Y1 > Y2) swap(Y1, Y2);

        cin >> n;
        Point O(0, 0);
        Point A(X1, Y1);
        Point B(X1, Y2);
        Point C(X2, Y2);
        Point D(X2, Y1);
        Line AB(A, B);
        Line BC(B, C);
        Line CD(C, D);
        Line DA(D, A);

        FOR(i,1,n) {
            cin >> p[i] >> v[i];
            if (v[i] != O) {
                l[i] = 1e100; r[i] = 0;

                if (!outside(p[i])) l[i] = 0.0;

                Point q = p[i] + v[i];
                Line t(p[i], q);

                update(AB, A, B, t, i);
                update(BC, B, C, t, i);
                update(CD, C, D, t, i);
                update(DA, D, A, t, i);
            }
            else if (!outside(p[i])) {
                l[i] = 0.0, r[i] = 1e30;
            }
            else l[i] = r[i] = 0.0;
        }

        double res = 1e100;

        FOR(i,1,n) FOR(j,i+1,n) {
            if (v[i] == O && outside(p[i])) continue;
            if (v[j] == O && outside(p[j])) continue;

            if (v[i] == O && v[j] == O) res = min(res, (p[i] - p[j]).len());
            else {
                res = min(res, get(i, j));
            }
        }

        if (res > 1e99) cout << "inf" << endl;
        else cout << res << endl;
    }
}
