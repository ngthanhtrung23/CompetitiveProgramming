#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const long double PI = acos((long double) -1.0);

struct Point {
    long double x, y;
    Point() { x = y = 0.0; }
    Point(long double x, long double y) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (long double k) { return Point(x*k, y*k); }

    long double sqlen() { return x*x + y*y; }
    long double len() { return sqrt(sqlen()); }

    void read() { cin >> x >> y; }
    void print() { cout << x << ' ' << y << endl; }
} P, Q;

struct Line {
    long double a, b, c;
    Point A, B;
    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a*A.x + b*A.y);
    }

    long double f(Point A) {
        return a*A.x + b*A.y + c;
    }
};

long double vp, v, r;

long double ab(long double x) {
    if (x < 0) return -x;
    else return x;
}

long double mysqrt(long double x) {
    if (ab(x) < 1e-9) x = 0;
    return sqrt(x);
}

bool order(Point A, Point B, Point C) {
    return ab((C-A).len() - (B-A).len() - (C-B).len()) < 1e-6;
}

vector<Point> cut(Line l, long double r) {
    long double a = l.a*l.a + l.b*l.b;
    long double b = 2*l.b*l.c;
    long double c = l.c*l.c - l.a*l.a*r*r;

    long double delta = b*b - 4*a*c;

    vector<Point> res; res.clear();
    if (ab(delta) < 1e-9) {
        delta = 0;
        long double x, y;
        y = -b / 2 / a;
        x = mysqrt(r*r - y*y);
        if (l.f(Point(x,y)) < 1e-3) {
            if (order(l.A, Point(x, y), l.B))
                res.PB(Point(x, y));
        }
        else {
            if (order(l.A, Point(-x, y), l.B))
                res.PB(Point(-x, y));
        }
    }
    else if (delta > 0) {
        long double x, y;
        y = (-b + sqrt(delta)) / 2 / a;
        x = mysqrt(r*r - y*y);
        if (ab(l.f(Point(x, y))) < 1e-3) {
            if (order(l.A, Point(x, y), l.B))
                res.PB(Point(x, y));
        }
        else {
            if (order(l.A, Point(-x, y), l.B))
                res.PB(Point(-x, y));
        }

        y = (-b - sqrt(delta)) / 2 / a;
        x = mysqrt(r*r - y*y);
        if (ab(l.f(Point(x, y))) < 1e-3) {
            if (order(l.A, Point(x, y), l.B))
                res.PB(Point(x, y));
        }
        else {
            if (order(l.A, Point(-x, y), l.B))
                res.PB(Point(-x, y));
        }
    }
    return res;
}

void refine(long double &d) {
    while (d > 2*PI) d -= 2*PI;
    while (d < 0) d += 2*PI;
}

long double cirlen(long double alpha1, long double alpha2) {
    long double d = alpha1 - alpha2;
    refine(d);
    long double res = r*d;
    d = 2*PI - d;
    refine(d);
    return min(res, r*d);
}

long double dist(Point Q, Point M) {
    Line l(Q, M);
    vector<Point> cur = cut(l, r);
    if (cur.size() < 2) return (Q-M).len();

    long double res = 0.0;
    res += sqrt(Q.sqlen() - r*r);
    res += sqrt(M.sqlen() - r*r);

    long double alpha1 = atan2(Q.y, Q.x);
    long double alpha2 = atan2(M.y, M.x);

    res += min(min(cirlen(alpha1 + acos(r / Q.len()), alpha2 + acos(r / M.len())),
                   cirlen(alpha1 + acos(r / Q.len()), alpha2 - acos(r / M.len()))),
               min(cirlen(alpha1 - acos(r / Q.len()), alpha2 + acos(r / M.len())),
                   cirlen(alpha1 - acos(r / Q.len()), alpha2 - acos(r / M.len()))));

    return res;
}

bool check(long double t) {
    long double R = P.len();

    long double alpha = atan2(P.y, P.x);
    long double tc = 2*PI*R/vp;

    alpha += t / tc * 2*PI;

    Point M(R*cos(alpha), R*sin(alpha));

    if (dist(Q, M) / v < t + 1e-9) return true;
    else return false;
}

int main() {
    ios :: sync_with_stdio(false);

    P.read(); cin >> vp;
    Q.read(); cin >> v >> r;

    cout << (fixed) << setprecision(10);

    long double res = 1e100, l = 0, r = 1e9;
    REP(turn,1000) {
        long double mid = (l + r) / 2.0;
        if (check(mid)) {
            res = mid;
            r = mid;
        }
        else {
            l = mid;
        }
    }
    cout << res << endl;
    return 0;
}
