
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

#define EPS 1e-6

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

struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double a = 0.0, double b = 0.0, double c = 0.0) : a(a), b(b), c(c) {} 

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

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d  = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

typedef vector< Point > Polygon;

Polygon polygon_cut(const Polygon& P, Line l) {
    Polygon Q;
    for(int i = 0; i < P.size(); ++i) {
        Point A = P[i], B = (i == P.size()-1) ? P[0] : P[i+1];
        if (ccw(l.A, l.B, A) != -1) Q.push_back(A);
        if (ccw(l.A, l.B, A)*ccw(l.A, l.B, B) < 0) {
            Point p; areIntersect(Line(A, B), l, p);
            Q.push_back(p);
        }
    }
    return Q;
}

double signed_area(Polygon p) {
    double area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}
double area(const Polygon &p) {
    return fabs(signed_area(p));
}

const int MN = 511;
int n, h, f;

pair<int,int> windows[MN];

pair<Line, Line> visible[2][MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> h >> f) {
        FOR(i,1,n) cin >> windows[i].first >> windows[i].second;

        Line topWall(Point(0, h), 0.0);
        Line bottomWall(Point(0, -h), 0.0);

        FOR(i,1,n) {
            visible[0][i].first  = Line(Point(0, f), Point(windows[i].first, h));
            visible[0][i].second = Line(Point(0, f), Point(windows[i].second, h));

            visible[1][i].first  = Line(Point(0, -f), Point(windows[i].first, -h));
            visible[1][i].second = Line(Point(0, -f), Point(windows[i].second, -h));
        }
        // calculate area visible from top light source
        double res = 0.0;
        FOR(i,1,n) {
            double top = windows[i].second - windows[i].first;
            Point A, B;
            assert(areIntersect(bottomWall, visible[0][i].first, A));
            assert(areIntersect(bottomWall, visible[0][i].second, B));

            double bottom = B.x - A.x;
            res += (top + bottom) * h;

//            DEBUG(res);
        }
        // calculate area visible from bottom light source
        // note that we must subtract intersection area
        FOR(i,1,n) {
            double bottom = windows[i].second - windows[i].first;
            Point A, B;
            assert(areIntersect(topWall, visible[1][i].first, A));
            assert(areIntersect(topWall, visible[1][i].second, B));

            double top = B.x - A.x;
            res += (top + bottom) * h;
//            DEBUG(res);

            Point C(windows[i].second, -h);
            Point D(windows[i].first, -h);

            // now we subtract intersection area
            FOR(j,1,n) {
                Polygon cur;
                cur.push_back(A);
                cur.push_back(B);
                cur.push_back(C);
                cur.push_back(D);

                Point X(windows[j].first, h);
                Point Y(windows[j].second, h);
                Point Z, T;
                areIntersect(bottomWall, visible[0][j].first, T);
                areIntersect(bottomWall, visible[0][j].second, Z);

                cur = polygon_cut(cur, Line(X, T));
                cur = polygon_cut(cur, Line(Z, Y));

                res -= area(cur);
            }
        }
        cout << (fixed) << setprecision(10) << res << endl;
    }
    return 0;
}

