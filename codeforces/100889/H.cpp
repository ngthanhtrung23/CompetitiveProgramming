#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define double long double
#define SZ(x) ((int) (x).size())
using namespace std;
int GI(int& x) {
    return scanf("%lld", &x);
}

#define EPS 1e-9

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

    double operator % (const Point& a) const { return x*a.y - y*a.x; } // cross product
    double operator * (const Point &a) const { return x*a.x + y*a.y; } // dot product

    double norm() { return x*x + y*y; }

    double len() { return hypot(x, y); }

    void read() {
        int t;
        GI(t); x = t;
        GI(t); y = t;
    }
};
ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}
int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));


const int MN = 300111;
int n, q;
Point a[MN], P, A, B;

#undef int
int main() {
#define int long long
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        GI(q);

        REP(i,n) a[i].read();
        FOR(i,n,n+n+n) a[i] = a[i-n];

        while (q--) {
            int u, x;
            GI(u); GI(x);

            A = a[u];
            B = a[(u + 1) % n];

            Point dir = B - A;
            P = A + dir / dir.len() * x;

            int l = u + 1, r = u + n - 1;
            double best = -1.0;
            int id = 0;

            while (l+10 <= r) {
                int mid = (l + r) >> 1;
                if (ccw(a[mid], a[mid+1], P) == RE_PHAI) {
                    l = mid;
                }
                else r = mid;
            }

            FOR(i,l,r) {
                if (ccw(a[i], a[i+1], P) == 0) {
                    printf("%lld %lld\n", i % n, (i+1) % n);
                    break;
                }
                if (ccw(a[i], a[i+1], P) == RE_TRAI) {
                    printf("%lld\n", i % n);
                    break;
                }
            }
        }
    }
}
