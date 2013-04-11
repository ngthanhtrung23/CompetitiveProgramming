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
const int MN = 2011;

long long f[MN][MN], sum[MN][MN], inc[MN][MN], g[MN][MN];

int main() {
    int m, n;
    while (cin >> m >> n) {
        memset(f, 0, sizeof f);
        memset(sum, 0, sizeof sum);
        memset(inc, 0, sizeof inc);

        f[0][0] = 1;
        FOR(i,1,m) {
            f[i][0] = 1; g[i][0] = 1;

            FOR(l,2,n) {
                f[i][l] = (sum[i-1][l] * (l+1) % MOD - inc[i-1][l] + f[i-1][0] + MOD) % MOD;
                sum[i][l] = (sum[i][l-1] + f[i][l]) % MOD;
                inc[i][l] = (inc[i][l-1] + l * f[i][l]) % MOD;

                g[i][l] = (f[i][l] - f[i-1][l] + MOD) % MOD;
            }
        }

        long long res = 0;
        FOR(u,1,m) FOR(l,2,n) {
            res = (res + g[u][l] * f[m-u+1][l] % MOD * (n + 1 - l)) % MOD;
            // cout << u << ' ' << l << ' ' << res << endl;
        }
        cout << res << endl;
    }
    return 0;
}
