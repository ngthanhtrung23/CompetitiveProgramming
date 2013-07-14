#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

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

int x1[11], x2[11], y1[11], y2[11], n;

#define TWO(x) (1<<(x))
#define CONTAIN(s,x) (s & TWO(x))

int main() {
    while (scanf("%d", &n) == 1) {
        REP(i,n) scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);

        bool ok = false;

        REP(s,TWO(n)) if (s == TWO(n) - 1) {
            int minx = 1000111000, maxx = -minx;
            int miny = minx, maxy = -miny;

            long long sum = 0;

            REP(i,n) if (CONTAIN(s,i)) {
                minx = min(minx, x1[i]);
                maxx = max(maxx, x2[i]);
                miny = min(miny, y1[i]);
                maxy = max(maxy, y2[i]);

                sum += (x2[i] - x1[i]) * (long long) (y2[i] - y1[i]);
            }

            if (maxx - minx != maxy - miny) continue;

            if ((maxx - minx) * (long long) (maxy - miny) == sum) {
                ok = true;
            }
        }

        if (ok) puts("YES"); else puts("NO");
    }
    return 0;
}
