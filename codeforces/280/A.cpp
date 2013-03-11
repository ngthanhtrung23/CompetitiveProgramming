#define _GLIBCXX_DEBUG
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
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

const long double PI = acos((long double) -1.0);
const long double EPS = 1e-6;

struct Point {
    long double x, y;

    Point() { x = y = 0.0; }
    Point(long double x, long double y) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (long double k) { return Point(x*k, y*k); }

    long double operator * (Point a) { return x*a.x + y*a.y; } // dot product
    long double operator % (Point a) { return x*a.y - y*a.x; } // cross product

    Point rotate(long double alpha) {
        long double sina = sin(alpha);
        long double cosa = cos(alpha);

        return Point(x*cosa - y*sina, x*sina + y*cosa);
    }

    void print() {
        cout << setprecision(2) << x << ' ' << y << endl;
    }
} A, B, C, D, AA, BB, CC, DD;

int cmp(long double x, long double y) {
   return (x < y+EPS) ? (x > y-EPS) ? 0 : -1 : 1;
}

struct Line {
    long double a, b, c;
    Point A, B;

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
};

int ccw(Point a, Point b, Point c) {
   return cmp((b-a)%(c-a),0); 
}

bool intersectSS(Line s, Line t) {
   if (ccw(s.A, s.B, t.A) == 0 && ccw(s.A, s.B, t.B) == 0) {
      if (max(t.A.x, t.B.x) < min(s.A.x, s.B.x) - EPS || max(s.A.x, s.B.x) < min(t.A.x, t.B.x) - EPS) return false;
      if (max(t.A.y, t.B.y) < min(s.A.y, s.B.y) - EPS || max(s.A.y, s.B.y) < min(t.A.y, t.B.y) - EPS) return false;
      return true;
   }
   return ccw(s.A, s.B, t.A) * ccw(s.A, s.B, t.B) <= 0 &&
         ccw(t.A, t.B, s.A) * ccw(t.A, t.B, s.B) <= 0;
}

Point crossPoint(Line l, Line m) {
   double A = (l.B - l.A) % (m.B - m.A);
   double B = (l.B - l.A) % (l.B - m.A);
   if (abs(A) < EPS && abs(B) < EPS) return m.A;
   return m.A + (m.B - m.A) * (B / A);
}

long double area(Point A, Point B, Point C) {
    return fabs(((B - A) % (C - A)) * 0.5);
}

int main() {
    cout << (fixed) << setprecision(9);
    long double w, h, a;
    while (cin >> w >> h >> a) {
        if (fabs(a - 0) <= 1e-6) {
            cout << w * h << endl;
            continue;
        }
        if (fabs(a - 90) <= 1e-6) {
            cout << sqr(min(w, h)) << endl;
            continue;
        }

        if (a > 90) a = 180 - a;
        a = a * PI / 180;

        A = Point(w/2, h/2);
        B = Point(-w/2, h/2);
        C = Point(-w/2, -h/2);
        D = Point(w/2, -h/2);

        AA = A.rotate(a);
        BB = B.rotate(a);
        CC = C.rotate(a);
        DD = D.rotate(a);

        // A.print(); B.print(); C.print(); D.print();
        // AA.print(); BB.print(); CC.print(); DD.print();

        Line AB(A, B);
        Line BC(B, C);
        Line CD(C, D);
        Line DA(D, A);
        Line AABB(AA, BB);
        Line DDAA(DD, AA);

        long double res = w * h;
        if (intersectSS(AB, AABB)) {
            Point M = crossPoint(AB, AABB);

            if (intersectSS(AABB, BC)) {
                Point N = crossPoint(AABB, BC);
                
                res -= 2 * area(M, N, B);

                Point P = crossPoint(DDAA, AB);
                Point Q = crossPoint(DDAA, DA);
                res -= 2 * area(P, Q, A);

                // M.print(); N.print(); P.print(); Q.print();
            }
            else {
                Point N = crossPoint(AABB, CD);
                Line CCDD(CC, DD);
                Point P = crossPoint(CCDD, CD);
                Point Q = crossPoint(CCDD, AB);

                res = area(M, N, P) + area(M, Q, P);
            }
        }
        else {
            Line BBCC(BB, CC);
            Line DDAA(DD, AA);
            Point M = crossPoint(BBCC, BC);
            Point N = crossPoint(BBCC, DA);
            Point P = crossPoint(DDAA, DA);
            Point Q = crossPoint(DDAA, BC);
            res = area(M, N, P) + area(M, Q, P);
        }

        cout << res << endl;
    }
    return 0;
}
