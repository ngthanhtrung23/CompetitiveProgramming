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

long long f[1011][1011][5];

void add(long long &a, long long b) {
    if (b < 0) return;
    a += b;
    if (a >= MOD) a %= MOD;
}

int main() {
    f[1][0][0] = 1;
    FOR(i,2,1000) {
        FOR(k,0,i) {
            // 0 : a[i] = i
            REP(x,5)
                add(f[i][k][0], f[i-1][k][x]);

            // 1 : a[i] = i-1, a[i-1] = i
            if (k > 1) f[i][k][1] = f[i-1][k-2][0];

            // 2 : a[i] = i-1, a[i-1] != i
            if (k > 0) {
                add(f[i][k][2], f[i-1][k][1]);
                add(f[i][k][2], f[i-1][k-1][2]);
                add(f[i][k][2], f[i-1][k][3]);
                add(f[i][k][2], f[i-1][k-1][4]);
            }

            // 3 : a[i] != i-1, a[i-1] = i
            if (k > 0) {
                add(f[i][k][3], f[i-1][k][1]);
                add(f[i][k][3], f[i-1][k][2]);
                add(f[i][k][3], f[i-1][k-1][3]);
                add(f[i][k][3], f[i-1][k-1][4]);
            }

            // 4 : a[i] != i-1, a[i-1] != i
            add(f[i][k][4], f[i-1][k+1][0] * (k+1));
            add(f[i][k][4], f[i-1][k+1][1] * (k-1));
            add(f[i][k][4], f[i-1][k+1][2] * k);
            add(f[i][k][4], f[i-1][k+1][3] * k);
            add(f[i][k][4], f[i-1][k+1][4] * (k+1));

            add(f[i][k][4], f[i-1][k][0] * (i-2-k));
            add(f[i][k][4], f[i-1][k][1] * (i-1-k));
            add(f[i][k][4], f[i-1][k][2] * (i-2-k));
            add(f[i][k][4], f[i-1][k][3] * (i-2-k));
            add(f[i][k][4], f[i-1][k][4] * (i-3-k));
        }
    }

    int k, n;
    while (cin >> n >> k) {
        long long res = 0;
        REP(t,5)
            add(res, f[n][k][t]);
        cout << res << endl;
    }
    return 0;
}
