
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
#define EPS 1e-8

inline int cmp(double a, double b) {
    if (fabs(a - b) < EPS) return 0;
    if (a < b) return -1;
    return 1;
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
    void read() {
        cin >> x >> y;
    }

    void print() {
        cout << x << ' ' << y << endl;
    }
} A1, B1, C1, D1, A2, B2, C2, D2, A3, B3, C3, D3;

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

Circle makeCircle(Point A, Point B, double k) {
    Point X = A + (B - A) * (k / (1+k));
    Point Y = A + (A - B) * (k / (1-k));

    Point res = (X + Y) / 2.0;
    return Circle(res.x, res.y, (res - X).len());
}

double s1, s2, s3;

typedef vector< Point > Polygon;

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

double angle(Point a, Point o, Point b) { // angle AOB
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}
bool in_polygon(const Polygon &P, Point pt) {
    if ((int)P.size() == 0) return false;
    double sum = 0;
    for (int i = 0; i < (int)P.size(); i++) {
        Point Pj = P[(i+1) % P.size()];
        // If allow on edge --> uncomment the following line
        // if (ccw(P[i], Pj, pt) == 0 && min(P[i], Pj) <= pt && pt <= max(P[i], Pj)) return true;
        if (ccw(pt, P[i], Pj) > 0)
            sum += angle(P[i], pt, Pj);
        else sum -= angle(P[i], pt, Pj);
    }
    return fabs(fabs(sum) - 2*acos(-1.0)) < EPS;
}

bool inside(Point x, Point a, Point b, Point c, Point d, bool debug = false) {
    Polygon p;
    p.push_back(a);
    p.push_back(b);
    p.push_back(c);
    p.push_back(d);

    return in_polygon(p, x);
}

bool check() {
    return inside(A2, A1, B1, C1, D1)
        && inside(B2, A1, B1, C1, D1)
        && inside(C2, A1, B1, C1, D1)
        && inside(D2, A1, B1, C1, D1)

        && inside(A3, A2, B2, C2, D2)
        && inside(B3, A2, B2, C2, D2)
        && inside(C3, A2, B2, C2, D2)
        && inside(D3, A2, B2, C2, D2);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);

    freopen("maps.in", "r", stdin);
    freopen("maps.out", "w", stdout);
    while (cin >> s1) {
        double X, Y; cin >> X >> Y;
        A1 = Point(0, 0);
        B1 = Point(X, 0);
        C1 = Point(X, Y);
        D1 = Point(0, Y);

        cin >> s2;
        cin >> s3;

        A3.read();
        B3.read();
        C3.read();
        D3.read();

        Circle c1 = makeCircle(A3, A1, s3 / s1);
        Circle c2 = makeCircle(B3, B1, s3 / s1);
        Circle c3 = makeCircle(C3, C1, s3 / s1);
        Circle c4 = makeCircle(D3, D1, s3 / s1);

        assert(areIntersect(c1, c2));
        auto all = circleIntersect(c1, c2);
        Point S = all[0];
//        S.print();

        double sa2 = (S - A3).len() * s2 / s3;
        double sb2 = (S - B3).len() * s2 / s3;
        double sc2 = (S - C3).len() * s2 / s3;
        double sd2 = (S - D3).len() * s2 / s3;

        const int C = 10000;
        bool ok = false;
        REP(turn,C) {
            double alpha = acos(-1.0) * 2.0 / C * turn;

            A2 = (A1 - S).rotate(alpha) / (A1 - S).len() * sa2 + S;
            B2 = (B1 - S).rotate(alpha) / (B1 - S).len() * sb2 + S;
            C2 = (C1 - S).rotate(alpha) / (C1 - S).len() * sc2 + S;
            D2 = (D1 - S).rotate(alpha) / (D1 - S).len() * sd2 + S;

            if (check()) {
                A2.print();
                B2.print();
                C2.print();
                D2.print();

                assert(inside(B3, A2, B2, C2, D2, true));
                ok = true;
                break;
            }
        }
        if (!ok) puts("impossible");

//        assert(areIntersect(c1, c3));
//        all = circleIntersect(c1, c3);
//        S = all[0];
//        S.print();
//
//        assert(areIntersect(c2, c3));
//        all = circleIntersect(c2, c3);
//        S = all[0];
//        S.print();
//
//        assert(areIntersect(c2, c4));
//        all = circleIntersect(c2, c4);
//        S = all[0];
//        S.print();
//
//        assert(areIntersect(c3, c4));
//        all = circleIntersect(c3, c4);
//        S = all[0];
//        S.print();
    }
}

