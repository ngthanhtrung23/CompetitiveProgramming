
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
#define double long double
#define EPS 1e-6
using namespace std;

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    
    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator * (double k) const { return Point(x*k, y*k); }
    Point operator / (double k) const { return Point(x/k, y/k); }

    Point conj() { return Point(-y, x); }

    double len() { return sqrt(x*x + y*y); }

    void read() {
        cin >> x >> y;
    }
    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

struct Line {
    double a, b, c;

    Line() {}

    Line(Point A, Point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
};

struct Circle : Point {
    double r;

    Circle() {}
    Circle(double x, double y, double r) : Point(x, y), r(r) {}

    void read() {
        Point::read();
        cin >> r;
    }
};

#define CIRCLE 0
#define LINE 1
struct Hieu {
    int typ; // CIRCLE or LINE
    Circle c;
    Line l;

    Hieu() {}
};

Hieu construct(Circle a, Circle b) {
    if (fabs(a.r - b.r) < EPS) {
        Point mid = (a + b) / 2.0;
        Point ab = b - a;

        Hieu res;
        res.typ = LINE;
        res.l = Line(mid, mid + ab.conj());
        return res;
    }
    else {
        Point ab = b - a;
        Point in = a + ab / (a.r + b.r) * a.r;
        Point out;

        if (a.r > b.r) {
            out = b + ab / (a.r - b.r) * b.r;
        }
        else {
            out = a - ab / (b.r - a.r) * a.r;
        }

        Point mid = (in + out) * 0.5;

        Hieu res;
        res.typ = CIRCLE;
        res.c = Circle(mid.x, mid.y, (in - mid).len());
        return res;
    }
}

bool hasSolution = false;
Point save;
double bestAngle;
bool check(Point X, Circle A, Circle B, Circle C) {
    double t1 = (A - X).len() / A.r;
    double t2 = (B - X).len() / B.r;
    double t3 = (C - X).len() / C.r;

    if (cmp(t1, t2)) return false;
    if (cmp(t2, t3)) return false;
    if (cmp(t1, t3)) return false;

    if (!hasSolution) {
        hasSolution = true;
        bestAngle = 2 * asin(A.r / (X - A).len());
        save = X;
    }
    else {
        double cur = 2 * asin(A.r / (X - A).len());
        if (cur > bestAngle) {
            save = X;
            bestAngle = cur;
        }
    }

    return true;
}

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

int main() {
    ios :: sync_with_stdio(false);
    Circle A, B, C;
    A.read();
    B.read();
    C.read();

    Hieu X = construct(A, B);
    Hieu Y = construct(B, C);

//    DEBUG(X.typ);
//    cout << X.l.a << ' ' << X.l.b << ' ' << X.l.c << endl;
//    DEBUG(Y.typ);
//    cout << Y.c.x << ' ' << Y.c.y << "   " << Y.c.r << endl;

    cout << (fixed) << setprecision(9);
    if (X.typ == LINE && Y.typ == LINE) {
        Point t;
        if (areIntersect(X.l, Y.l, t)) {
            check(t, A, B, C);
        }
    }
    else if (X.typ + Y.typ == LINE + CIRCLE) {
        if (X.typ == CIRCLE) swap(X, Y);
        auto all = intersection(X.l, Y.c);
        for(auto t : all) {
            check(t, A, B, C);
        }
    }
    else if (X.typ == CIRCLE && Y.typ == CIRCLE) {
        if (areIntersect(X.c, Y.c)) {
            auto all = circleIntersect(X.c, Y.c);
            for(auto t : all) {
                check(t, A, B, C);
            }
        }
    }
    if (hasSolution) {
        cout << save.x << ' ' << save.y << endl;
    }
}

