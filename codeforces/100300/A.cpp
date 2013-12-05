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

long double H, R, D1, h1, D2, h2, D, n;

long double cube(long double x = n) {
    return x * n * n;
}

long double cylinder(long double h) {
    return h * M_PI * R * R;
}

void add(long double x) {
    long double v = cylinder(h1 + h2) + cube(x);
    long double h = v / M_PI / R / R;

    if (h > H) h = H;

    cout << h << endl;
}

int main() {
    cout << (fixed) << setprecision(10);
    while (cin >> H >> R >> D1 >> h1 >> D2 >> h2 >> D >> n) {
        long double max1 = cylinder(h1) / (M_PI*R*R - n*n);
        long double max2 = cylinder(h2) / (M_PI*R*R - n*n);

        if (D <= D2) {
            long double x = n*D / D2;
            if (x <= max2) {
                add(x);
                continue;
            }
        }
        if (D <= D1) {
            long double y = (n*D - max2*D2) / D1;
            if (y <= max1) {
                long double x = max2 + y;
                if (x > n) x = n;
                add(x);
                continue;
            }
        }
        long double x = cylinder(h1+h2) / (M_PI * R * R - n*n);
        if (x > n) x = n;
        add(x);
    }
    return 0;
}
