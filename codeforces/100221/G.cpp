
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
#define EPS 1e-6
const int MN = 211;
const double PI = acos((double) -1.0);

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
} a[MN];
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}
double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}

int n;
double r;
Point O(0, 0);
Point hor;
double res;
Point save;

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
double f(double alpha) {
    Point P = hor.rotate(alpha);
    Point l = a[1], r = a[1];
    FOR(i,2,n) {
        int t = ccw(P, l, a[i]);
        if (t < 0) l = a[i];

        t = ccw(P, r, a[i]);
        if (t > 0) r = a[i];
    }
    double cur = angle(l, P, r);
    if (cur > res) {
        res = cur;
        save = P;
    }
    return cur;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("secret.in", "r", stdin);
    freopen("secret.out", "w", stdout);

    cout << (fixed) << setprecision(9);

    while (cin >> n >> r) {
        FOR(i,1,n) cin >> a[i];
        hor = Point(r, 0);

        const int NROT = 100;
        res = -1.0;
        REP(i,NROT) {
            double l = 2*PI / NROT * i;
            double r = 2*PI / NROT * (i + 1);

            REP(turn,100) {
                double x1 = (l + l + r) / 3.0;
                double x2 = (l + r + r) / 3.0;

                double y1 = f(x1);
                double y2 = f(x2);

                if (y1 > y2) r = x2;
                else l = x1;
            }
        }

        cout << save << endl;
    }
}
