
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const double EPS = 1e-6;
inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

inline double det(double a, double b, double c, double d) {
    return a * d - b * c;
}
struct Point {
    double x, y, z;
    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    double length() {
        return sqrt(x * x + y * y + z * z);
    }
    Point operator * (double a) const { return Point(x*a, y*a, z*a); }
    double operator * (Point a) const { return x*a.x + y*a.y + z*a.z; }
    Point operator + (Point a) { return Point(x+a.x, y+a.y, z+a.z); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y, z-a.z); }
    Point operator %(const Point &op) const {
        return Point(det(y, z, op.y, op.z), -det(x, z, op.x, op.z), det(x, y,
                op.x, op.y));
    }

    Point normalize() {
        double l = length();
        return Point(x/l, y/l, z/l);
    }

    bool read() {
        if (!(cin >> x >> y >> z)) return false;
        return true;
    }
    void print() {
        cout << x << ' ' << y << ' ' << z << endl;
    }
} A, B, X, Y;

Point project(Point P, Point i, Point j, Point k) {
    return Point(P * i, P * j, P * k);
}

double getDist(Point A, double h, double R) {
    double to_h = 0;
    if (A.z < 0) to_h = 0 - A.z;
    else if (A.z > h) to_h = A.z - h;

    double to_plane = max(0.0, sqrt(A.x*A.x + A.y*A.y) - R);
    return sqrt(sqr(to_plane) + sqr(to_h));
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(12);
    freopen("tracing.in", "r", stdin);
    freopen("tracing.out", "w", stdout);
    while (A.read()) {
        B.read();
        double R; cin >> R;
        X.read(); Y.read();

        // 1. First, we transform all the points to new co-ordinate system, with:
        // - O  = A (cylinder center)
        // - Oz = (cylinder axis).normalize()
        // - Ox, Oy = 2 perpendicularvectors on cylinder base
        Point O = A;
        A = A - O;
        B = B - O;
        X = X - O;
        Y = Y - O;

        Point Oz = (B - A).normalize();
        Point rand_point = Point(141.12731, 892.19284, 712.12347);
        Point Ox = (Oz % rand_point).normalize();
        Point Oy = (Oz % Ox).normalize();


        A = project(A, Ox, Oy, Oz);
        B = project(B, Ox, Oy, Oz);
        X = project(X, Ox, Oy, Oz);
        Y = project(Y, Ox, Oy, Oz);

        Point Ix = project(Point(1, 0, 0), Ox, Oy, Oz);
        Point Iy = project(Point(0, 1, 0), Ox, Oy, Oz);
        Point Iz = project(Point(0, 0, 1), Ox, Oy, Oz);

        // 2. Ternary search to find 1st point with distance <= 0 to cylinder
        double l = 0, r = 1e10;
        REP(turn,10000) {
            double x1 = (l + l + r) / 3.0;
            double x2 = (l + r + r) / 3.0;
            double y1 = getDist(X + (Y - X) * x1, B.z, R);
            double y2 = getDist(X + (Y - X) * x2, B.z, R);

            if (cmp(y1, 0) == 0 || y1 < y2) {
                r = x2;
            }
            else l = x1;
        }
        Point P = X + (Y - X) * l;
        if (cmp(getDist(P, B.z, R), EPS) > 0) {
            cout << "NONE" << endl;
            continue;
        }

        // 3. Transform back the result to original co-ordinate system
        P = project(P, Ix, Iy, Iz);
        P = P + O;

        P.print();
    }
    return 0;
}

