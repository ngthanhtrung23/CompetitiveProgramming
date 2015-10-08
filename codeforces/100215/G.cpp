
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

#define EPS 1e-6
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

    void read() {
        cin >> x >> y;
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

double distToLine(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p-c).len();
}

double f[211][211];
int tr[211][211];
double toa[211], tob[211];
Point a[211];
int c[211], res[211];

void trace(int n, int k) {
    if (n == 0) return ;

    res[n] = tr[n][k];
    if (tr[n][k] == 1) trace(n-1, k-1);
    else trace(n-1, k);
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("pipe.in", "r", stdin);
    freopen("pipe.out", "w", stdout);

    int n, C;
    while (cin >> n >> C) {
        Point A1, A2, B1, B2;
        A1.read(); A2.read();
        B1.read(); B2.read();

        FOR(i,1,n) {
            a[i].read();
            cin >> c[i];

            Point tmp;
            toa[i] = distToLine(a[i], A1, A2, tmp) * c[i];
            tob[i] = distToLine(a[i], B1, B2, tmp) * c[i];
        }

        FOR(i,0,n) FOR(j,0,n) f[i][j] = 1e20;
        f[0][0] = 0;
        FOR(i,1,n) {
            FOR(j,0,i) {
                if (j) {
                    f[i][j] = f[i-1][j-1] + toa[i];
                    tr[i][j] = 1;
                }
                double cur = f[i-1][j] + tob[i];
                if (cur < f[i][j]) {
                    f[i][j] = cur;
                    tr[i][j] = 2;
                }
            }
        }
        double best = 1e20;
        int save = -1;
        FOR(x,0,n) {
            int y = n - x;
            if (abs(x - y) <= C && f[n][x] < best) {
                best = f[n][x];
                save = x;
            }
        }
        trace(n, save);
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
}
