
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

#define double long double

const double EPS = 1e-9;

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    friend istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y;
        return cin;
    }

    friend ostream& operator << (ostream& cout, Point& p) {
        cout << p.x << ' ' << p.y;
        return cout;
    }
};

struct Line {
    double a, b, c;

    Line(Point A, Point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }

    friend ostream& operator << (ostream& cout, Line& l) {
        cout << l.a << ' ' << l.b << ' ' << l.c << endl;
        return cout;
    }

    double dist(Point p) {
        return fabs(a*p.x + b*p.y + c) / sqrt(a*a + b*b);
    }
};

#define y1 y1_____
double y1, y2, yw, R;
Point ball;

double f(double x) {
    Point wall(x, yw);
    Point ref(2 * x - ball.x, ball.y);  // reflection of the ball

    Line l(wall, ref);

    return - l.c / l.b;
}

bool check(double x) {
    Point wall(x, yw);
    Point ref(2 * x - ball.x, ball.y);  // reflection of the ball

    Line l(wall, ref);
    if (l.dist(Point(0, y2)) < R) {
        return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(12);

    while (cin >> y1 >> y2 >> yw >> ball >> R) {
        double l = EPS, r = ball.x - EPS, res = -1.0;

        yw -= R;  // now we can consider ball as 1 point

        REP(turn,1000) {
            double mid = (l + r) / 2.0;
            if (f(mid) > y1 + R) {
                res = mid;
                l = mid;
            }
            else r = mid;
        }
        if (!check(res)) res = -1.0;
        cout << res << endl;
    }
}
