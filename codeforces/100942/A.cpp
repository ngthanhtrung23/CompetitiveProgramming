#include <bits/stdc++.h>
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
    Point perp() { return Point(-y, x); }
    double norm() { return x*x + y*y; }

    double len() { return sqrt(norm()); }

    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
struct Circle : Point {
    double r;
    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}
    Circle(Point p, double r) : Point(p), r(r) {}
    
    bool contains(Point p) { return (*this - p).len() <= r + EPS; }
};
Circle getCircumcircle(Point a, Point b, Point c) {
    double d = 2.0 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    assert(fabs(d) > EPS);
    double x = (a.norm() * (b.y - c.y) + b.norm() * (c.y - a.y) + c.norm() * (a.y - b.y)) / d;
    double y = (a.norm() * (c.x - b.x) + b.norm() * (a.x - c.x) + c.norm() * (b.x - a.x)) / d;
    Point p(x, y);
    return Circle(p, (p - a).len());
}

vector< Point > get(Point X, Point Y, double alpha) {
    Point M = (X + Y) * 0.5;
    Point dir = (Y - X).perp();

    double need = (M - X).len() / tan(alpha / 2.0);
    dir = dir * (need / dir.len());

    vector<Point> res;
    res.push_back(M + dir);
    res.push_back(M - dir);
    return res;
}

bool areIntersect(Circle u, Circle v) {
    if (cmp((u - v).len(), u.r + v.r) > 0) return false;
    if (cmp((u - v).len() + v.r, u.r) < 0) return false;
    if (cmp((u - v).len() + u.r, v.r) < 0) return false;
    return true;
}
vector<Point> circleIntersect(Circle u, Circle v) {
    if (cmp(u.x, v.x) == 0
            && cmp(u.y, v.y) == 0
            && cmp(u.r, v.r) == 0) {
        vector<Point> res;
        FOR(i,1,5) {
            Point P = u + Point(0, u.r);
            P = (P - u).rotate(i) + u;
            res.push_back(P);
        }
        return res;
    }
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
double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

int main() {
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        Point X, Y, Z;
        double alpha, beta;
        scanf("%lf%lf", &X.x, &X.y);
        scanf("%lf%lf", &Y.x, &Y.y);
        scanf("%lf%lf", &Z.x, &Z.y);
        scanf("%lf%lf", &alpha, &beta);

        alpha = DEG_to_RAD(alpha);
        beta = DEG_to_RAD(beta);

        auto A = get(X, Y, alpha);
        auto B = get(Y, Z, beta);

        vector<Circle> C1, C2;
        C1.push_back(getCircumcircle(A[0], X, Y));
        C1.push_back(getCircumcircle(A[1], X, Y));

        C2.push_back(getCircumcircle(B[0], Y, Z));
        C2.push_back(getCircumcircle(B[1], Y, Z));

        for(auto c1 : C1) for(auto c2 : C2) {
            auto p = circleIntersect(c1, c2);
            for(auto pp : p) {
                if (cmp(angle(X, pp, Y), alpha) == 0
                        && cmp(angle(Y, pp, Z), beta) == 0
                        && pp != X
                        && pp != Y
                        && pp != Z) {
                    printf("%.9lf %.9lf", pp.x, pp.y);
                    goto done;
                }
            }
        }
done:
        puts("");
    }
}
