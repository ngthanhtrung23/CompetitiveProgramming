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
using namespace std;

const long double EPS = 1e-6;

typedef complex<long double> Point;
Point A, B;

void read(Point &a) {
    long double x, y;
    cin >> x >> y;
    a = Point(x, y);
}

long double cross(const Point& a, const Point& b) { return imag(conj(a)*b); }
long double dot(const Point& a, const Point& b) { return real(conj(a)*b); }

#define X real()
#define Y imag()
;

int ccw(Point a, Point b, Point c) {
   b -= a; c -= a;
   if (cross(b, c) > EPS)   return +1;       // counter clockwise
   if (cross(b, c) < -EPS)   return -1;       // clockwise
// if used for convex hull, do not include the next 2 lines
   if (dot(b, c) < -EPS)     return +2;       // c--a--b on line
   if (norm(b) < norm(c)) return -2;       // a--b--c on line
   return 0;
}

struct Segment {
    Point A, B;

    Point projection(Point p) {
        long double t = dot(p-A, A-B) / norm(A-B);
        return A + t*(A-B);
    }

    bool intersect(Segment a) { // modified
       if (ccw(A, B, a.A) < EPS && ccw(A, B, a.B) < EPS) {
          if (max(a.A.X,a.B.X) < min(A.X,B.X) || max(A.X,B.X) < min(a.A.X,a.B.X)) return false;
          if (max(a.A.Y,a.B.Y) < min(A.Y,B.Y) || max(A.Y,B.Y) < min(a.A.Y,a.B.Y)) return false;
          return true; 
       }
       return ccw(A,B,a.A)*ccw(A,B,a.B) < EPS &&
             ccw(a.A,a.B,A)*ccw(a.A,a.B,B) < EPS;
    }

    bool intersect(Point p) {
        return abs(A-p)+abs(B-p)-abs(A-B) < EPS;
    }

    long double distance(Point p) {
        const Point r = projection(p);
        if (intersect(r)) return abs(r - p);
        return min(abs(A - p), abs(B - p));
    }

    long double distance(Segment a) {
        if (intersect(a)) return 0;

        return min(min(distance(a.A), distance(a.B)),
                min(a.distance(A), a.distance(B)));
    }
} x[1011];

long double a, b, f[1011];
int n;
bool mark[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a >> b) {
        read(A); read(B);
        cin >> n;
        FOR(i,1,n) {
            read(x[i].A); read(x[i].B);
        }
        x[n+1].A = x[n+1].B = A;
        x[n+2].A = x[n+2].B = B;

        FOR(i,1,n+2) f[i] = 1e100;
        f[n+1] = 0;
        memset(mark, false, sizeof mark);
        FOR(turn,1,n+2) {
            int u = -1;
            FOR(i,1,n+2) if (!mark[i])
                if (u == -1 || f[i] < f[u])
                    u = i;
            if (u < 0) break;
            mark[u] = true;

            FOR(i,1,n+2) {
                if (x[u].distance(x[i]) < a + EPS) {
                    if (i == n+2)
                        f[i] = min(f[i], f[u] + x[u].distance(x[i]));
                    else f[i] = min(f[i], f[u] + a + b);
                }
            }
        }

        if (f[n+2] == 1e100) cout << -1 << endl;
        else cout << (fixed) << setprecision(10) << f[n+2] << endl;
    }
    return 0;
}
