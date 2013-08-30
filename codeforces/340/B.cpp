#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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

struct Point {
    long long x, y;

    Point(long long x = 0, long long y = 0) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    long long operator % (Point a) { return x*a.y - y*a.x; }
} a[311];

inline long long ab(long long x) {
    if (x < 0) return -x;
    else return x;
}

long long area(Point a, Point b, Point c) {
    return ab((b - a) % (c - a));
}

struct Line {
    Point A, B;
    long long a, b, c;

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }

    long long f(Point A) {
        return a * A.x + b * A.y + c;
    }
};

int n;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].x >> a[i].y;

        long long res = 0;
        FOR(i,1,n) FOR(j,i+1,n) {
            Line l(a[i], a[j]);

            long long max1 = 0, max2 = 0;
            FOR(k,1,n) {
                long long f = l.f(a[k]);

                if (f < 0) max1 = max(max1, area(a[i], a[j], a[k]));
                else if (f > 0) max2 = max(max2, area(a[i], a[j], a[k]));
            }
            if (max1 && max2)
                res = max(res, max1 + max2);
        }
        cout << (res / 2) << '.' << (res % 2) * 5 << endl;
    }
    return 0;
}
