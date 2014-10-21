#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const long double EPS = 1e-6;

struct Point {
    long double x, y;
    Point(long double x = 0, long double y = 0) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    long double sqlen() { return x*x + y*y; }
    long double len() { return sqrt(sqlen()); }

    void print() { cout << x << ' ' << y << endl; }
} points[111], O(0, 0);

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    long double t = b.x*c.y - b.y*c.x;
    if (fabs(t) < EPS) return 0;
    else if (t < 0) return -1;
    else return 1;
}

bool operator < (const Point &a, const Point &b) {
    int t = ccw(O, a, b);
    if (t == 0) return (const_cast<Point &>(a)).sqlen() < (const_cast<Point &>(b)).sqlen();
    return t > 0;
}

long double area(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    long double t = b.x*c.y - b.y*c.x;
    return fabs(t) / 2.0;
}

struct Rect {
    Point A, B, C, D;
} a[111];
int n;

long double X, Y;
int nPoint;

struct Line { long double a, b, c; };          // a way to represent a line

void pointsToLine(Point p1, Point p2, Line &l) {
    if (fabs(p1.x - p2.x) < EPS) {              // vertical line is fine
        l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;           // default values
    } else {
        l.a = -(long double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;              // IMPORTANT: we fix the value of b to 1.0
        l.c = -(long double)(l.a * p1.x) - p1.y;
    } 
}

bool areParallel(Line l1, Line l2) {       // check coefficients a & b
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;            // no intersection
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // special case: test for vertical line to avoid division by zero
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else                  p.y = -(l2.a * p.x + l2.c);
    return true;
}

bool between(Point A, Point B, Point P) {
    return min(A.x, B.x) - EPS <= P.x && P.x <= max(A.x, B.x) + EPS
            && min(A.y, B.y) - EPS <= P.y && P.y <= max(A.y, B.y) + EPS;
}

void go(Point A, Point B, Line lA, Line lB, Point &X, Point &Y) {
    if ((A.x > EPS || A.y > EPS) && (B.x > EPS || B.y > EPS)) {
        Line l; pointsToLine(A, B, l);
        Point P, Q;
        if (areIntersect(l, lA, P) && areIntersect(l, lB, Q)) {
            if (between(A, B, P) && between(A, B, Q)) {
                if (P.len() < X.len()) X = P;
                if (Q.len() < Y.len()) Y = Q;
            }
        }
    }
}

long double calc() {
    nPoint = 0;
    FOR(i,1,n) {
        points[++nPoint] = a[i].A;
        points[++nPoint] = a[i].B;
        points[++nPoint] = a[i].C;
        points[++nPoint] = a[i].D;
    }
    sort(points+1, points+nPoint+1);
    long double res = 0.0;
    FOR(i,1,nPoint-1) {
        Point A = points[i], B = points[i+1];

        // cout << "Khe: " << A.x << ' ' << A.y << ' ' << B.x << ' ' << B.y << endl;
        Line lA, lB;
        pointsToLine(O, A, lA);
        pointsToLine(O, B, lB);

        Point X(1e5, 1e5), Y(1e5, 1e5);

        FOR(r,1,n) {
            Line l;
            go(a[r].A, a[r].B, lA, lB, X, Y);
            go(a[r].B, a[r].C, lA, lB, X, Y);
            go(a[r].C, a[r].D, lA, lB, X, Y);
            go(a[r].D, a[r].A, lA, lB, X, Y);
        }

        res += area(O, X, Y);
        // DEBUG(res);
    }
    // cout << endl;
    return res;
}

void xoay(Point &P, int turn) {
    if (turn == 0) {
        P.x = X - P.x;
    } else {
        P.y = Y - P.y;
    }
}

void reverse(int turn) {
    FOR(i,1,n) {
        xoay(a[i].A, turn);
        xoay(a[i].B, turn);
        xoay(a[i].C, turn);
        xoay(a[i].D, turn);
    }
}

int main(int argc, char const *argv[]) {
    int ntest; cin >> ntest;
    cout << (fixed) << setprecision(6);
    while (ntest--) {
        cin >> X >> Y >> n;
        FOR(i,1,n) {
            long double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);

            a[i].A = Point(x1, y1);
            a[i].B = Point(x1, y2);
            a[i].C = Point(x2, y2);
            a[i].D = Point(x2, y1);
        }
        ++n;
        a[n].A = Point(0, 0);
        a[n].B = Point(0, Y);
        a[n].C = Point(X, Y);
        a[n].D = Point(X, 0);

        long double res3 = calc();

        reverse(0);
        long double res4 = calc();

        reverse(1);
        long double res2 = calc();

        reverse(0);
        long double res1 = calc();

        cout << res1 << ' ' << res2 << endl << res3 << ' ' << res4 << endl;
    }
    return 0;
}