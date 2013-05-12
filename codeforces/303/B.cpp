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

long long X, Y, x, y, a, b;

#define moveX(val) { int t = val; x1 += t; x2 += t; }
#define moveY(val) { int t = val; y1 += t; y2 += t; }

#define sqr(x) ((x) * (x))

int main() {
    while (cin >> X >> Y >> x >> y >> a >> b) {
        int g = __gcd(a, b);
        a /= g; b /= g;
        int can = min(X / a, Y / b);
        int lx = can * a, ly = can * b;

        X *= 2; Y *= 2; lx *= 2; ly *= 2;
        x *= 2; y *= 2;

        long long x1, y1, x2, y2;
        x1 = x - lx / 2;
        y1 = y - ly / 2;
        x2 = x1 + lx; y2 = y1 + ly;

        if (x1 < 0) moveX(-x1);
        if (y1 < 0) moveY(-y1);

        if (x2 > X) moveX(-(x2 - X));
        if (y2 > Y) moveY(-(y2 - Y));

        x1 /= 2; y1 /= 2; x2 /= 2; y2 /= 2;

        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
    }
    return 0;
}
