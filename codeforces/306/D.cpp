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

struct Point {
    long double x, y;

    Point() { x = y = 0; }
    Point(long double x, long double y) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (long double k) { return Point(x*k, y*k); }

    Point rotate(long double alpha) {
        long double sina = sin(alpha), cosa = cos(alpha);
        return Point(x*cosa - y*sina, x*sina + y*cosa);
    }

    void print() {
        cout << x << ' ' << y << endl;
        // cout << '(' << x << ", " << y << ')' << endl;
    }
} a[111];

struct Line {
    Point A, B;
    long double a, b, c;

    Line() {
    }
    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
};

Point cross(Line l1, Line l2) {
    long double dx = l1.b*l2.c - l1.c*l2.b;
    long double dy = l1.c*l2.a - l1.a*l2.c;
    long double d  = l1.a*l2.b - l1.b*l2.a;

    return Point(dx / d, dy / d);
}

int DIAM;

int main() {
    cout << (fixed) << setprecision(6);
    int n;
    while (cin >> n) {
        if (n < 5) {
            puts("No solution");
            continue;
        }
        DIAM = 70 * n;
        a[1] = Point(DIAM, 0);
        FOR(i,2,n) a[i] = a[i-1].rotate(2 * PI / n);

        a[n+1] = a[1]; a[n+2] = a[2]; a[0] = a[n];
        FOR(i,1,n) {
            if (i == n) break;
            int j = i+1; if (j > n) j = 1;

            Line l1(a[i-1], a[i]);
            Line l2(a[i+1], a[i+2]);

            Point P = (a[i] + a[i+1]) * 0.5;

            P = P * ((DIAM + (i*0.1)) / (long double) DIAM);

            Line old(a[i], a[i+1]);

            Line l; l.a = old.a; l.b = old.b;
            l.c = - (l.a * P.x + l.b * P.y);

            a[i] = cross(l, l1);
            a[j] = cross(l, l2);

            a[n+1] = a[1]; a[n+2] = a[2]; a[0] = a[n];
        }

        FOR(i,1,n) a[i].print();
    }
}
