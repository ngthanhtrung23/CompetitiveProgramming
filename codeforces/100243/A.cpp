
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

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (double k) { return Point(x*k, y*k); }
    Point operator / (double k) { return Point(x/k, y/k); }

    double operator * (Point a) { return x*a.x + y*a.y; } // dot product
    double operator % (Point a) { return x*a.y - y*a.x; } // cross product

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

double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}

double directed_angle(Point a, Point o, Point b) { // angle AOB, in range [0, 2*PI)
    double t = -atan2(a.y - o.y, a.x - o.x)
            + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2*PI;
    return t;
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
struct Circle : Point {
    double r;
    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}
    Circle(Point p, double r) : Point(p), r(r) {}
    
    bool contains(Point p) { return (*this - p).len() <= r + EPS; }
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

ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}

double f(const Circle& c1, double a, const Circle& c2, double l, double r) {
    Point hor1(c1.x + c1.r, c1.y);
    Point hor2(c2.x + c2.r, c2.y);

    Point A1 = (hor1 - c1).rotate(a) + c1;

    double res = 1e9;
    REP(turn,100) {
        double x1 = (l + l + r) / 3;
        double x2 = (l + r + r) / 3;

        Point A2 = (hor2 - c2).rotate(x1) + c2;
        Point B2 = (hor2 - c2).rotate(x2) + c2;

        double y1 = (A1 - A2).len();
        double y2 = (A1 - B2).len();

        res = min(res, min(y1, y2));

        if (y1 < y2) r = x2;
        else l = x1;
    }
    return res;
}

double go(Circle c1, double u1, double v1, Circle c2, double u2, double v2) {
    double res = 1e9;
    double l = u1, r = v1;
    REP(turn,100) {
        double x1 = (l + l + r) / 3;
        double x2 = (l + r + r) / 3;

        double y1 = f(c1, x1, c2, u2, v2);
        double y2 = f(c1, x2, c2, u2, v2);

        res = min(res, min(y1, y2));

        if (y1 < y2) r = x2;
        else l = x1;
    }
    return res;
}

double solve(Circle c1, double start1, double last1, Circle c2, double start2, double last2) {
    if (start1 > last1) {
        return min(
                solve(c1, start1, 2*PI, c2, start2, last2),
                solve(c1, 0, last1, c2, start2, last2)
                );
    }
    if (start2 > last2) {
        return min(
                solve(c1, start1, last1, c2, start2, 2*PI),
                solve(c1, start1, last1, c2, 0, last2)
                );
    }

    const int STEP = 4;
    double each1 = (last1 - start1) / STEP;
    double each2 = (last2 - start2) / STEP;
    double res = 1e9;

    double u1 = start1, u2;
    REP(i,STEP) {
        double v1 = u1 + each1;

        u2 = start2;
        REP(j,STEP) {
            double v2 = u2 + each2;

            res = min(res, go(c1, u1, v1, c2, u2, v2));

            u2 = v2;
        }

        u1 = v1;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("circular.in", "r", stdin);
    freopen("circular.out", "w", stdout);
    Circle c1, c2;
    double start1, last1, start2, last2;
    cout << (fixed) << setprecision(9);
    while (cin >> c1.x >> c1.y >> c1.r >> start1 >> last1) {
        cin >> c2.x >> c2.y >> c2.r >> start2 >> last2;

        start1 = DEG_to_RAD(start1);
        last1 = DEG_to_RAD(last1);
        start2 = DEG_to_RAD(start2);
        last2 = DEG_to_RAD(last2);

        auto res = solve(c1, start1, last1, c2, start2, last2);
        cout << res << endl;
    }
}
