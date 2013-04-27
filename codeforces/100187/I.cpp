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
const int MN = 2011;

int n, b[MN];
long long a[MN][MN];

int main() {
    while (scanf("%d", &n) == 1) {
        b[0] = 1;
        FOR(i,1,n) scanf("%d", &b[i]);

        bool ok = true;
        FORD(i,n,1) {
            int last = n - i + 1;
            // Xay dung a[i]
            if (b[i-1] == 1) { // All a[i] should be > 0
                long long nn = 1000111000111000LL;
                FORD(j,last,1) {
                    if (j == last) a[i][j] = 1;
                    else a[i][j] = a[i][j+1] - a[i+1][j];
                    nn = min(nn, a[i][j]);
                }

                if (nn <= 0) {
                    FOR(j,1,last)
                        a[i][j] = a[i][j] - nn + 1;
                }
            }
            else { // All a[i] should be < 0
                long long ln = -1000111000111000LL;
                FORD(j,last,1) {
                    if (j == last) a[i][j] = -1;
                    else a[i][j] = a[i][j+1] - a[i+1][j];
                    ln = max(ln, a[i][j]);
                }

                if (ln >= 0) {
                    FOR(j,1,last)
                        a[i][j] = a[i][j] - ln - 1;
                }
            }

            long long nn = a[i][1], ln = a[i][1];
            FOR(j,1,n) {
                nn = min(nn, a[i][j]);
                ln = max(ln, a[i][j]);
            }

            if (ln - nn > 2000000000) {
                ok = false;
                break;
            }
            if (i == 1) {
                FOR(j,1,n) a[1][j] = a[1][j] - nn - 1000000000;
            }
        }
        if (!ok) {
            puts("IMPOSSIBLE");
            continue;
        }

        FOR(i,1,1) {
            FOR(j,1,n) printf("%d ", a[i][j]);
            puts("");
        }
        puts("");
    }
    return 0;
}
