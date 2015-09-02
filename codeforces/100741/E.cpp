
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const double EPS = 1e-6;
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

bool order(const Point& a, const Point& b, const Point& c) {
    return min(a.x, c.x) - EPS <= b.x && b.x <= max(a.x, c.x) + EPS
        && min(a.y, c.y) - EPS <= b.y && b.y <= max(a.y, c.y) + EPS;
}


typedef vector< Point > Polygon;

int main() {
    ios :: sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        Polygon p; Polygon line;
        p.resize(n); line.resize(m);
        REP(i,n) cin >> p[i].x >> p[i].y;
        REP(i,m) cin >> line[i].x >> line[i].y;

//        cerr << "OK" << endl;

        double res = 0.0;
        bool in = false;
        REP(i,m-1) {
            Point A = line[i], B = line[i+1];
            Line cur(A, B);
            set< Point > all;
            all.insert(A);
            all.insert(B);

            REP(j,n) {
                Point X = p[j], Y = p[(j+1)%n];
                Line l(X, Y);

                Point t;
                if (areIntersect(cur, l, t)) {
                    if (order(A, t, B) && order(X, t, Y)) 
                        all.insert(t);
                }
            }

            vector< Point > v(all.begin(), all.end());
            if (v.back() == A) reverse(v.begin(), v.end());

            int start = 0;
            if (!in) start = 1;
            for(int i = start; i+1 < v.size(); i += 2)
                res += (v[i] - v[i+1]).len();

            if (v.size() % 2 == 1) in = !in;

//            for(auto p : v) cout << p.x << ' ' << p.y << "    "; cout << endl;
//            DEBUG(res);
//            DEBUG(in);
        }
        res *= 2;
        REP(i,n) res += (p[i] - p[(i+1) % n]).len();
        cout << (fixed) << setprecision(9) << res << endl;
    }
}

