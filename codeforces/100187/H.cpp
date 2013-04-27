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
    long long x, y;
    Point() { x = y = 0; }
    Point(long long x, long long y) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    long long sqlen() { return x*x + y*y; }

    bool read() { return cin >> x >> y; }
};

bool check(long long a1, long long b1, long long c1, long long a2, long long b2, long long c2) {
    return (a1 * b2 == a2 * b1 && b1 * c2 == b2 * c1);
}

int main() {
    Point A1, A2, B1, B2, C1, C2;
    while (A1.read()) {
        B1.read(); C1.read();
        A2.read(); B2.read(); C2.read();

        long long a1 = (A1 - B1).sqlen(), b1 = (B1 - C1).sqlen(), c1 = (C1 - A1).sqlen();
        long long a2 = (A2 - B2).sqlen(), b2 = (B2 - C2).sqlen(), c2 = (C2 - A2).sqlen();

        if (check(a1, b1, c1, a2, b2, c2)
                || check(a1, b1, c1, a2, c2, b2)
                || check(a1, b1, c1, b2, a2, c2)
                || check(a1, b1, c1, b2, c2, a2)
                || check(a1, b1, c1, c2, a2, b2)
                || check(a1, b1, c1, c2, b2, a2))
            puts("YES");
        else puts("NO");
    }
    return 0;
}
