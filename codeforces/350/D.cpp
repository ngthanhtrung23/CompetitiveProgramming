#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

struct Line {
    int a, b, c;

    Line() {}

    Line(int x1, int y1, int x2, int y2, bool rot = false) {
        a = y2 - y1;
        b = x1 - x2;
        if (rot) {
            swap(a, b);
            a = -a;
        }
        int g = __gcd(a, b);
        a /= g; b /= g;
        if (a < 0) a = -a, b = -b;

        c = - (a * x1 + b * y1);
    }
} a[300111];

bool operator < (const Line &x, const Line &y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

struct Event {
    int a, b, c;
    int x, y;
    int type;

    Event(int a, int b, int c, int x, int y, int type) 
        : a(a), b(b), c(c), x(x), y(y), type(type) {}

    Event() {}
};

bool operator < (const Event &a, const Event &b) {
    if (a.a != b.a) return a.a < b.a;
    if (a.b != b.b) return a.b < b.b;
    if (a.c != b.c) return a.c < b.c;
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.type < b.type;
}

Event event[3000111];

struct Circle {
    int x, y, r;
} b[1511];

int n, m;

#define sqr(x) ((x)*(x))

int main() {
    GN(n); GN(m);
    int x1, y1, x2, y2;
    int nEvent = 0;
    FOR(i,1,n) {
        GN(x1); GN(y1); GN(x2); GN(y2);
        x1 *= 2; y1 *= 2; x2 *= 2; y2 *= 2;

        a[i] = Line(x1, y1, x2, y2);
        // cout << a[i].a << ' ' << a[i].b << ' ' << a[i].c << endl;

        if (x2 < x1 || (x2 == x1 && y2 < y1)) {
            swap(x1, x2);
            swap(y1, y2);
        }
        event[++nEvent] = Event(a[i].a, a[i].b, a[i].c, x1, y1, 1);
        event[++nEvent] = Event(a[i].a, a[i].b, a[i].c, x2, y2, 3);
    }

    FOR(i,1,m) {
        GN(b[i].x); GN(b[i].y); GN(b[i].r);
        b[i].x *= 2; b[i].y *= 2;
        b[i].r *= 2;
    }

    FOR(i,1,m) FOR(j,i+1,m)
    if (b[i].r == b[j].r && 4*b[i].r*b[i].r < sqr(b[i].x-b[j].x) + sqr(b[i].y-b[j].y)) {
        Line l(b[i].x, b[i].y, b[j].x, b[j].y, true);

        int x = (b[i].x + b[j].x) / 2;
        int y = (b[i].y + b[j].y) / 2;
        l.c = - (l.a * x + l.b * y);
        // cout << l.a << ' ' << l.b << ' ' << l.c << endl;

        event[++nEvent] = Event(l.a, l.b, l.c, x, y, 2);
    }

    int res = 0;
    sort(event+1, event+nEvent+1);
    int now = 0;
    FOR(i,1,nEvent) {
        if (i == 1 || event[i].a != event[i-1].a || event[i].b != event[i-1].b || event[i].c != event[i-1].c)
            now = 0;
        if (event[i].type == 1) ++now;
        else if (event[i].type == 3) --now;
        else res += now;
    }
    cout << res << endl;

    return 0;
}
