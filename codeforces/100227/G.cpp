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
};

struct Line {
    long long a, b, c;
    Point A, B;

    Line(Point A = Point(0, 0), Point B = Point(0,0)) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }

    int side(Point P) {
        long long t = a * P.x + b * P.y + c;
        if (t < 0) return -1;
        else if (t == 0) return 0;
        else return 1;
    }
} l[111];

struct Object {
    Point a[11];
    char label;
    int sz;
} a[111];

int c[111][111], nObj, p;

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

void solve(int i, int mask) {
    if (mask == 0) return ;

    if (i > p) {
        FOR(i,1,nObj)
        if (CONTAIN(mask,i-1)) {
            cout << a[i].label;
        }
        return ;
    }

    int good = l[i].side(Point(0, -1000111000));

    int s1 = 0, s2 = 0;
    FOR(o,1,nObj) if (CONTAIN(mask, o-1)) {
        int cur = l[i].side(a[o].a[1]);

        if (cur * good < 0) s1 |= TWO(o-1);
        else s2 |= TWO(o-1);
    }
    solve(i+1, s1);
    solve(i+1, s2);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nObj) {
        memset(c, 0, sizeof c);
        FOR(i,1,nObj) {
            cin >> a[i].sz;
            a[i].label = 'A' + i - 1;
            FOR(t,1,a[i].sz) {
                cin >> a[i].a[t].x >> a[i].a[t].y;
            }
        }
        cin >> p;
        FOR(i,1,p) {
            Point A, B; cin >> A.x >> A.y >> B.x >> B.y;
            l[i] = Line(A, B);
        }
        solve(1, TWO(nObj) - 1);
        cout << endl;
    }
    return 0;
}
