#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int NANGLE = 211;
const int NDIVIDE = 55;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    Point rotate(double alpha) {
        double sina = sin(alpha), cosa = cos(alpha);
        return Point(-sina*x + cosa*y, cosa*x + sina*y);
    }

    void print() { cout << x << ' ' << y << endl; }
} a[211], save[211];

struct vec {
    double x, y;  // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {}
};
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

int n;
double r;

vec toVec(Point a, Point b) {       // convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y);
}
double angle(Point a, Point o, Point b) {  // returns angle aob in rad
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    double t = b.x*c.y - b.y*c.x;
    if (fabs(t) < 1e-6) return 0;
    else if (t < 0) return -1;
    else return 1;
}

double calc() {
    Point O = Point(0, -r);
    Point L = Point(-1, -r);
    Point R = Point(1, -r);
    swap(L, R);

    FOR(i,1,n) {
        if (ccw(O, L, a[i]) == 1) L = a[i];
        if (ccw(O, R, a[i]) == -1) R = a[i];
    }

    return angle(L, O, R);
}

double get(double ang) {
    FOR(i,1,n) a[i] = save[i].rotate(ang);
    return calc();
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> r) {
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            save[i] = a[i];
        }

        double each = M_PI * 2 / NANGLE, res = 0;

        REP(turn,NANGLE) {
            double from = each * turn, to = (each + 1) * turn;

            REP(rot,NDIVIDE) {
                double x1 = (from + from + to) / 3.0;
                double x2 = (from + to + to) / 3.0;

                double y1 = get(x1);
                double y2 = get(x2);

                res = max(res, max(y1, y2));

                if (y1 > y2) to = x2;
                else from = x1;
            }
        }
        cout << (fixed) << setprecision(9) << res << endl;
    }
    return 0;
}
