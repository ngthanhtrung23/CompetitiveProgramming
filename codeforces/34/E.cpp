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

struct Ball {
    double x, v, m;
} a[11];
int n;

const double EPS = 1e-6;

double collisionTime(Ball a, Ball b) {
    if (a.x > b.x) swap(a, b);

    if (a.v < 0 && b.v > 0) return 1e10;

    if (a.v >= 0 && b.v <= 0) {
        if (fabs(a.v) + fabs(b.v) < 1e-9) return 1e10;
        return (b.x - a.x) / (fabs(a.v) + fabs(b.v));
    }
    else {
        if (fabs(fabs(a.v) - fabs(b.v)) < 1e-9) return 1e10;
        if (a.v >= 0 && b.v >= 0 && a.v > b.v) return (b.x - a.x) / (a.v - b.v);
        if (a.v <= 0 && b.v <= 0 && fabs(a.v) < fabs(b.v))
            return (b.x - a.x) / (fabs(b.v) - fabs(a.v));
    }
    return 1e10;
}

double get() {
    double res = 1e10;
    FOR(i,1,n) FOR(j,1,n) if (fabs(a[i].x - a[j].x) > EPS) {
        res = min(res, collisionTime(a[i], a[j]));
    }
    return res;
}

void update(double t) {
    FOR(i,1,n) a[i].x = a[i].x + a[i].v * t;

    FOR(i,1,n) FOR(j,i+1,n) {
        if (fabs(a[i].x - a[j].x) < EPS) {
            double v1 = ((a[i].m - a[j].m) * a[i].v + 2 * a[j].m * a[j].v) / (a[i].m + a[j].m);
            double v2 = ((a[j].m - a[i].m) * a[j].v + 2 * a[i].m * a[i].v) / (a[i].m + a[j].m);
            a[i].v = v1; a[j].v = v2;
        }
    }
}

int main() {
    cout << fixed << setprecision(9);
    while (cin >> n) {
        double t;
        cin >> t;
        FOR(i,1,n) cin >> a[i].x >> a[i].v >> a[i].m;

        double passed = 0;
        while (true) {
            double col = get();
            double mint = col + passed;
            if (mint > t) break;

            passed = mint;
            update(col);

            // FOR(i,1,n) cout << a[i].x << ' ' << a[i].v << ' ' << a[i].m << endl;
        }
        if (passed < t) update(t - passed);
        FOR(i,1,n)
            cout << a[i].x << endl;
    }
    return 0;
}