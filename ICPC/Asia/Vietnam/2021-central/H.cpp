
#include "bits/stdc++.h"

#define int long long
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

#define EPS 1e-6
const double PI = acos(-1.0);

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    Point() { x = y = 0.0; }
    Point(double _x, double _y) : x(_x), y(_y) {}

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
    Circle(double _x = 0, double _y = 0, double _r = 0) : Point(_x, _y), r(_r) {}
    Circle(Point p, double _r) : Point(p), r(_r) {}
    
    bool contains(Point p) { return (*this - p).len() <= r + EPS; }

    double area() const { return r*r*M_PI; }

    // definitions in https://en.wikipedia.org/wiki/Circle
    // assumption: 0 <= theta <= 2*PI
    // theta: angle in radian
    double sector_area(double theta) const {
        return 0.5 * r * r * theta;
    }

    // assumption: 0 <= theta <= 2*PI
    // theta: angle in radian
    double segment_area(double theta) const {
        return 0.5 * r * r * (theta - sin(theta));
    }
};
istream& operator >> (istream& cin, Circle& p) {
    cin >> p.x >> p.y >> p.r;
    return cin;
}

// Distance from p to Line ab (closest Point --> c)
double distToLine(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p-c).len();
}

double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {} 

    Line(Point _A, Point _B) : A(_A), B(_B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
    Line(Point P, double m) {
        a = -m; b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point p) {
        return a*p.x + b*p.y + c;
    }
};

vector<Point> intersection(Line l, Circle cir) {
    double r = cir.r, a = l.a, b = l.b, c = l.c + l.a*cir.x + l.b*cir.y;
    vector<Point> res;

    double x0 = -a*c/(a*a+b*b),  y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS) return res;
    else if (fabs(c*c - r*r*(a*a+b*b)) < EPS) {
        res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
        return res;
    }
    else {
        double d = r*r - c*c/(a*a+b*b);
        double mult = sqrt (d / (a*a+b*b));
        double ax,ay,bx,by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

        res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
        res.push_back(Point(bx, by) + Point(cir.x, cir.y));
        return res;
    }
}
double area(Point a, Point b, Point c) {
    double p = (a - c) % (b - c);
    return fabs(p) * 0.5;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    Point A, B;
    Circle C;
    double p;
    cin >> A >> B >> C >> p;

    Point H;
    double dist = distToLine(C, A, B, H);
    if (cmp(dist, C.r) >= 0) {
        cout << "NO" << endl;
        return 0;
    }

    Line AB(A, B);
    auto intersections = intersection(AB, C);
    assert(intersections.size() == 2);

    Point u = intersections[0];
    Point v = intersections[1];

    double alpha = angle(u, C, v);

    double smaller_perc = C.segment_area(alpha) / C.area();

    p *= 0.01;
    cout << ((smaller_perc >= p - 0.05 && smaller_perc <= p + 0.05)
            ? "YES"
            : "NO") << endl;

    return 0;
}
