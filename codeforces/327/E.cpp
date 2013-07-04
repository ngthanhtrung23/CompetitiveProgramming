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
const long long MOD = 1000000007LL;
const int oo = 1000000001;

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

int n, a[25], x[25], k;
int sum[TWO(24)], f[TWO(24)];

int main() {
    while (scanf("%d", &n) == 1) {
        REP(i,n) {
            scanf("%d", &a[i]);
            sum[TWO(i)] = a[i];
        }
        x[1] = x[2] = -1;
        scanf("%d", &k);
        FOR(i,1,k) scanf("%d", &x[i]);

        f[0] = 1; sum[0] = 0;
        int u;
        REP(mask,TWO(n)) if (mask) {
            if (__builtin_popcount(mask) > 1) {
                u = mask & (-mask);
                sum[mask] = sum[mask - u] + sum[u];
                if (sum[mask] > oo) sum[mask] = oo;
            }

            if (sum[mask] == x[1] || sum[mask] == x[2]) {
                f[mask] = 0;
            }
            else {
                f[mask] = 0;
                for(int i = 0; i < n; ++i)
                    if (CONTAIN(mask,i)) {
                        f[mask] += f[mask - TWO(i)];
                        if (f[mask] >= MOD) f[mask] -= MOD;
                    }
            }
        }
        cout << f[TWO(n)-1] << endl;
    }
    return 0;
}
