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
const long long BASE = 1000000007LL;

long long power(long long x, long long k) {
    if (k == 0) return 1;
    if (k == 1) return x % BASE;
    long long mid = power(x, k >> 1);
    mid = (mid * mid) % BASE;   
    if (k & 1) return (mid * x) % BASE;
    else return mid;
}

long long f[111][10111], g[111][111], c[111][111];
long long m;
int n;

int main() {
    c[0][0] = 1;
    FOR(i,1,100) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = (c[i-1][j-1] + c[i-1][j]) % BASE;
    }

    long long k;
    while (cin >> n >> m >> k) {
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);

        FOR(i,1,n) FOR(x,0,n) {
            long long k = (m - i) / n + 1;
            g[i][x] = power(c[n][x], k);
        }

        f[0][0] = 1;

        FOR(i,0,n-1) FOR(s,0,k) if (f[i][s] > 0) {
            FOR(x,0,n) if (s+x <= k) {
                f[i+1][s+x] += f[i][s] * g[i+1][x];
                f[i+1][s+x] %= BASE;
            }
        }
        cout << f[n][k] << endl;
    }
    return 0;
}
