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
const int MN = 200111;

int n, sl[2], m;
pair<int,int> a[2][MN];
int eu[MN], ev[MN], ec[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        memset(sl, 0, sizeof sl);
        m = 0;

        FOR(i,1,n) {
            int c, s; scanf("%d%d", &c, &s);
            ++sl[c]; a[c][sl[c]] = MP(s, i);
        }

        sort(a[0] + 1, a[0] + sl[0] + 1);
        sort(a[1] + 1, a[1] + sl[1] + 1);

        int i = 0, j = 0;
        while (i < sl[0] || j < sl[1]) {
            if (a[0][i].F == 0 && i < sl[0]) ++i;
            if (a[1][j].F == 0 && j < sl[1]) ++j;

            int can = min(a[0][i].F, a[1][j].F);
            a[0][i].F -= can;
            a[1][j].F -= can;

            ++m;
            eu[m] = a[0][i].S;
            ev[m] = a[1][j].S;
            ec[m] = can;

            if (a[0][i].F == 0 && i < sl[0]
                    && a[1][j].F == 0 && j < sl[1]) {
                ++m;
                eu[m] = a[0][i].S;
                ev[m] = a[1][j+1].S;
                ec[m] = 0;
            }
        }

        FOR(i,1,m) printf("%d %d %d\n", eu[i], ev[i], ec[i]);
        puts("");
    }
    return 0;
}
