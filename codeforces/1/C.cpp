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

long double sina, cosa;

struct Point {
    long double x, y;
    Point() { x = y = 0; }
    Point(long double x, long double y) : x(x), y(y) {}
    void read() { cin >> x >> y; }

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (long double k) { return Point(x*k, y*k); }

    Point vg() { return Point(-y, x); }
    Point rotate() { return Point(x*cosa - y*sina, x*sina + y*cosa); }

    long double sqlen() { return x*x + y*y; }
    long double len() { return sqrt(sqlen()); }
} A, B, C, O;

struct Line {
    long double a, b, c;
    Point A, B;

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a*A.x + b*A.y);
    }
};

Point cut(Line l1, Line l2) {
    long double d  = l1.a*l2.b - l1.b*l2.a;
    long double dx = l1.b*l2.c - l1.c*l2.b;
    long double dy = l1.c*l2.a - l1.a*l2.c;

    return Point(dx/d, dy/d);
}

long double ab(long double x) {
    if (x < 0) return -x;
    else return x;
}

bool same(Point a, Point b) {
    return ab(a.x-b.x) < 1e-4 && ab(a.y-b.y) < 1e-4;
}

long double alpha;

bool check(int n) {
    Point P = A;
    bool okB = false, okC = false;
    sina = sin(alpha); cosa = cos(alpha);
    FOR(i,1,n) {
        P = (P-O).rotate() + O;
        if (same(B, P)) okB = true;
        if (same(C, P)) okC = true;
    }
    return okB && okC;
}

int main() {
    ios :: sync_with_stdio(false);
    A.read(); B.read(); C.read();
    if (same(A, B) && same(B, C)) {
        puts("0.000000");
        return 0;
    }
    if (same(A, B) || same(B, C) || same(C, A)) {
        long double l = ((B-A).len() + (C-B).len() + (A-C).len()) / 2;
        cout << (fixed) << setprecision(10) << l*l*sqrt(3) / 4 << endl;
        return 0;
    }
    Point M = (A + B) * 0.5;
    Point M2 = M + (B-A).vg();
    Line l(M, M2);

    Point P = (B + C) * 0.5;
    Point P2 = P + (C-B).vg();
    Line m(P, P2);

    O = cut(m, l);
    long double res = 0.0, PI = acos((long double) -1.0), R = (O - A).len();

    FOR(i,3,100) {
        alpha = 2*PI / i;
        if (check(i)) {
            res = i*0.5*R*R*sin(alpha);
            break;
        }
    }
    cout << (fixed) << setprecision(10) << res << endl;
    return 0;
}
