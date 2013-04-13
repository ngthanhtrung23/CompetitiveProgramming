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

struct Segment {
    int pos, u, v;
} hor[611], ver[611];

int n, nHor, nVer;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    while (scanf("%d", &n) == 1) {
        nHor = nVer = 0;
        FOR(i,1,n) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            if (x1 == x2) {
                nVer++;
                ver[nVer].pos = x1;
                ver[nVer].u = min(y1, y2);
                ver[nVer].v = max(y1, y2);
            }
            else {
                nHor++;
                hor[nHor].pos = y1;
                hor[nHor].u = min(x1, x2);
                hor[nHor].v = max(x1, x2);
            }
        }

        long long res = 0;
        FOR(i,1,nVer) FOR(j,i+1,nVer) {
            int l = max(ver[i].u, ver[j].u);
            int r = min(ver[i].v, ver[j].v);
            if (l >= r) continue;

            int x1 = min(ver[i].pos, ver[j].pos);
            int x2 = max(ver[i].pos, ver[j].pos);

            int cnt = 0;
            FOR(k,1,nHor) {
                if (hor[k].pos >= l && hor[k].pos <= r)
                    if (hor[k].u <= x1 && hor[k].v >= x2)
                        ++cnt;
            }

            res += cnt * (cnt - 1) / 2;
        }
        cout << res << endl;
    }
    return 0;
}
