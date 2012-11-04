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

int n, h;
pair<int,int> a[100111];
int res[100111];

int main() {
    while (scanf("%d%d", &n, &h) == 2) {
        FOR(i,1,n) {
            scanf("%d", &a[i].F);
            a[i].S = i;
        }
        if (n == 2) {
            puts("0");
            puts("1 1");
            continue;
        }
        sort(a+1, a+n+1);

        int best = 1000111000, save = 0;
        FOR(first,0,n) {
            int ln = -1, nn = 1000111000;
            if (first == 1) {
                nn = min(a[1].F + a[2].F + h, a[2].F + a[3].F);
            }
            else {
                nn = a[1].F + a[2].F;
            }

            if (first == n-1) {
                ln = a[n].F + a[n-1].F + h;
            }
            else {
                ln = a[n].F + a[n-1].F;
                if (first) {
                    ln = max(ln, a[n].F + a[first].F + h);
                }
            }

            int now = ln - nn;
            if (now < best) {
                best = now;
                save = first;
            }
        }

        FOR(i,1,save) res[a[i].S] = 1;
        FOR(i,save+1,n) res[a[i].S] = 2;

        printf("%d\n", best);
        FOR(i,1,n) printf("%d ", res[i]);
        puts("");
    }
    return 0;
}
