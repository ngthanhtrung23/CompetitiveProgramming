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

int m, n;
char a[111][10111];
int l[111][10111], r[111][10111];

bool all0(int i) {
    FOR(j,1,n)
        if (a[i][j] == '1') return false;
    return true;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        bool ok = true;
        FOR(i,1,m) if (all0(i)) {
            ok = false;
            break;
        }
        if (!ok) puts("-1");
        else {
            int res = 1000111000;

            FOR(i,1,m) {
                int j = 1;
                while (a[i][j] == '0') ++j;

                int prev = j, savej = j;
                FOR(turn,1,n) {
                    if (a[i][j] == '1') l[i][j] = 0;
                    else l[i][j] = l[i][prev] + 1;

                    prev = j;
                    j++; if (j > n) j = 1;
                }

                j = savej; prev = j;
                FOR(turn,1,n) {
                    if (a[i][j] == '1') r[i][j] = 0;
                    else r[i][j] = r[i][prev] + 1;

                    prev = j;
                    --j; if (j < 1) j = n;
                }
            }

            FOR(j,1,n) {
                int cur = 0;
                FOR(i,1,m) cur += min(l[i][j], r[i][j]);

                res = min(res, cur);
            }
            cout << res << endl;
        }
    }
    return 0;
}
