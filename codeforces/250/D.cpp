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
const int MN = 100111;

struct Point {
    long long x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    long double len() {
        return sqrt(x*x + y*y);
    }
} trai[MN], phai[MN];
int len[MN];

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    long long t = b.x * c.y - b.y * c.x;
    if (t == 0) return 0;
    else if (t < 0) return -1;
    else return 1;
}

long double res;
int savel, saver;

void update(int i, int j) {
    long double cur = trai[i].len() + (phai[j] - trai[i]).len() + len[j];

    if (cur < res) {
        res = cur;
        savel = i;
        saver = j;
    }
}

int main() {
    int a, b, n, m;
    while (scanf("%d%d%d%d", &n, &m, &a, &b) == 4) {
        FOR(i,1,n) {
            int y; scanf("%d", &y);
            trai[i] = Point(a, y);
        }
        FOR(i,1,m) {
            int y; scanf("%d", &y);
            phai[i] = Point(b, y);
        }
        FOR(i,1,m) scanf("%d", &len[i]);

        res = 1e100;
        savel = 0, saver = 0;

        int i = 1;
        FOR(j,1,m) {
            while (i < n && ccw(Point(0,0), trai[i], phai[j]) > 0) {
                ++i;
            }
            // cout << j << ' ' << i << endl;

            update(i, j);
            if (i > 1) update(i-1, j);
        }

        printf("%d %d\n", savel, saver);
    }
    return 0;
}