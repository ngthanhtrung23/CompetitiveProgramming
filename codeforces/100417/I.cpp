
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
#define double long double
using namespace std;

const int MN = 111;
#define EPS 1e-9
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
    double norm() { return x*x + y*y; }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return sqrt(norm()); }

    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ',' << p.y;
    return cout;
}

double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}

double directed_angle(Point a, Point o, Point b) { // angle AOB, in range [0, 2*PI)
    double t = -atan2(a.y - o.y, a.x - o.x)
            + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2*PI;
    return t;
}

// Distance from p to Line ab (closest Point --> c)
double distToLine(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p-c).len();
}

// Distance from p to segment ab (closest Point --> c)
double distToLineSegment(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    if (u < 0.0) {
        c = Point(a.x, a.y);
        return (p - a).len();
    }
    if (u > 1.0) {
        c = Point(b.x, b.y);
        return (p - b).len();
    }
    return distToLine(p, a, b, c);
}

// NOTE: WILL NOT WORK WHEN a = b = 0.
struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double a, double b, double c) : a(a), b(b), c(c) {} 

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
    Line(Point P, double m) {
        a = -m; b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point A) {
        return a*A.x + b*A.y + c;
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

Line bisector(Point A, Point B, Point C) {
    Point bc = C - B;
    return Line(B, A + bc * ((A - B).len() / bc.len()));
}

Point a[111][111];
int na[111];
double x[111];
Point v[111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	freopen("roof.in", "r", stdin);
	freopen("roof.out", "w", stdout);
    cout << (fixed) << setprecision(9);
    int n;
	while (cin >> n) {
		FOR(i,1,n) cin >> a[0][i];
		na[0] = n;

        double res = 0.0;
		FOR(time,1,n) {
			int nprev = na[time-1];

			a[time-1][0] = a[time-1][nprev];
			a[time-1][nprev+1] = a[time-1][1];
			a[time-1][nprev+2] = a[time-1][2];

            double mint = 1e15;
			FOR(i,1,nprev) {
                Point P = a[time-1][i];
                Point Q = a[time-1][i+1];

                Point A = a[time-1][i-1];
                Point B = a[time-1][i+2];

                Line l1 = bisector(A, P, Q);
                Line l2 = bisector(P, Q, B);

                Point X;
                assert(areIntersect(l1, l2, X));

                // time taken to move P --> X
                x[i] = (P - X).len() * sin(angle(A, P, X));
                if (x[i] < 0) x[i] = -x[i];

                // velocity P --> X
                v[i] = (X - P) / x[i];
                mint = min(mint, x[i]);
			}

            FOR(i,1,nprev) {
                a[time][i] = a[time-1][i] + v[i] * mint;
                res += (a[time][i] - a[time-1][i]).len();
            }
            int ncur = 0;
            FOR(i,1,nprev) {
                if (i == 1 || a[time][i] != a[time][i-1]) {
                    ++ncur;
                    a[time][ncur] = a[time][i];
                }
            }
            while (ncur > 1 && a[time][ncur] == a[time][1]) --ncur;
            na[time] = ncur;

//            DEBUG(ncur);
//            FOR(i,1,ncur) DEBUG(a[time][i]);

            if (ncur == 1) break;

            if (ncur == 2) {
                res += (a[time][1] - a[time][2]).len();
                break;
            }
		}
        cout << res << endl;
	}
}

