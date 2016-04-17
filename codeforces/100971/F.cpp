
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
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

#define EPS 1e-6
inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    Point() { x = y = 0; }
    Point(double x, double y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }

    double sqlen() { return x*x + y*y; }
    double len() { return sqrt(sqlen()); }
};
bool operator == (const Point& a, const Point& b) {
    return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0;
}

istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}

struct Line {
    double a, b, c;
    Line(double a, double b, double c) : a(a), b(b), c(c) {} 
    Line(Point A, Point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
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

bool order(Point a, Point b, Point c) {
    return cmp(min(a.x, c.x), b.x) <= 0 && cmp(b.x, max(a.x, c.x)) <= 0
        && cmp(min(a.y, c.y), b.y) <= 0 && cmp(b.y, max(a.y, c.y)) <= 0;
}

void closestPoint(Line l, Point p, Point &ans) {
    if (fabs(l.b) < EPS) {
        ans.x = -(l.c) / l.a; ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS) {
        ans.x = p.x; ans.y = -(l.c) / l.b;
        return;
    }
    Line perp(l.b, -l.a, - (l.b*p.x - l.a*p.y));
    areIntersect(l, perp, ans);
}

Point a, b, va, vb, aa, bb;
double solve() {
    aa = a + va;
    bb = b + vb;
    Line la(a, aa);
    Line lb(b, bb);
    Point O(0, 0);

    if (va == O && vb == O) {
        return (a - b).len();
    }
    if (vb == O) {
        swap(va, vb);
    }
    if (va == O) {
        double res = (a - b).len();
        Point p; closestPoint(lb, a, p);
        if (!order(p, b, bb)) {
            res = min(res, (a - p).len());
        }
        return res;
    }

    Point p;
    double res = (a - b).len();
    if (areIntersect(la, lb, p)) {
        if (!order(p, a, aa) && !order(p, b, bb)) res = 0.0;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(15);

    while (cin >> a >> b >> va >> vb) {
        vb = vb - va;
        va = Point(0, 0);
        cout << solve() << endl;
    }
}
