
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
#define sqr(x) ((x) * (x))
#define double long double
using namespace std;

const double PI = acos((double) -1.0);

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y);
    }
    double len() {
        return hypot(x, y);
    }
};

struct Circle : Point {
    double r;
};

double solve(double a, double b, double c) {
    return acos((a*a + b*b - c*c) / 2 / a / b);
}

double cut(double a, double r) {
    double s1 = a * r * r / 2;
    double s2 = sin(a) * r * r / 2;
    return s1 - s2;
}

double commonCircleArea(Circle c1, Circle c2) { //return the common area of two circle
    if (c1.r < c2.r) {
        swap(c1, c2);
    }
    double d = (c1 - c2).len();
    double a1 = solve(d, c1.r, c2.r);
    double a2 = solve(d, c2.r, c1.r);
    return cut(a1*2, c1.r) + cut(a2*2, c2.r);
}

int main() {
    cout << (fixed) << setprecision(12);
    ll x1, y1, r1, x2, y2, r2;
    while (cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2) {
        // do not intersect
        ll dist2 = sqr(x1 - x2) + sqr(y1 - y2);
        if (dist2 >= sqr(r1 + r2)) {
            cout << 0.0 << endl;
            continue;
        }
        
        // C1 in C2
        double dist = sqrt(dist2);
        if (dist + r1 <= r2) {
            cout << PI * r1 * r1 << endl;
            continue;
        }
        // C2 in C1
        if (dist + r2 <= r1) {
            cout << PI * r2 * r2 << endl;
            continue;
        }

        Circle c1; c1.x = x1; c1.y = y1; c1.r = r1;
        Circle c2; c2.x = x2; c2.y = y2; c2.r = r2;
        cout << commonCircleArea(c1, c2) << endl;
    }
}
