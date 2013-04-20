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

#define __ [40][40][40][40]

int n, m;
int x __, f1 __, f2 __, f3 __, f4 __, l[40], r[40], block[40];

int main() {
    freopen("hyper.in", "r", stdin);
    freopen("hyper.out", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i1,1,n) FOR(i2,1,n) FOR(i3,1,n) FOR(i4,1,n) scanf("%d", &x[i1][i2][i3][i4]);

        memset(block, -1, sizeof block);
        FOR(i,1,n) {
            if ((i-1) % m == 0) block[i] = block[i-1] + 1;
            else block[i] = block[i-1];
        }

        FOR(i1,1,n) FOR(i2,1,n) FOR(i3,1,n) {
            FOR(i4,1,n) {
                if (block[i4] == block[i4-1])
                    l[i4] = min(l[i4-1], x[i1][i2][i3][i4]);
                else l[i4] = x[i1][i2][i3][i4];
            }
            FORD(i4,n,1) {
                if (block[i4] == block[i4+1])
                    r[i4] = min(r[i4+1], x[i1][i2][i3][i4]);
                else r[i4] = x[i1][i2][i3][i4];
            }
            FOR(i4,1,n-m+1)
                f1[i1][i2][i3][i4] = min(r[i4], l[i4+m-1]);
        }

        FOR(i1,1,n) FOR(i2,1,n) FOR(i4,1,n-m+1) {
            FOR(i3,1,n) {
                if (block[i3] == block[i3-1])
                    l[i3] = min(l[i3-1], f1[i1][i2][i3][i4]);
                else l[i3] = f1[i1][i2][i3][i4];
            }
            FORD(i3,n,1) {
                if (block[i3] == block[i3+1])
                    r[i3] = min(r[i3+1], f1[i1][i2][i3][i4]);
                else r[i3] = f1[i1][i2][i3][i4];
            }
            FOR(i3,1,n-m+1)
                f2[i1][i2][i3][i4] = min(r[i3], l[i3+m-1]);
        }

        FOR(i1,1,n) FOR(i3,1,n-m+1) FOR(i4,1,n-m+1) {
            FOR(i2,1,n) {
                if (block[i2] == block[i2-1])
                    l[i2] = min(l[i2-1], f2[i1][i2][i3][i4]);
                else l[i2] = f2[i1][i2][i3][i4];
            }
            FORD(i2,n,1) {
                if (block[i2] == block[i2+1])
                    r[i2] = min(r[i2+1], f2[i1][i2][i3][i4]);
                else r[i2] = f2[i1][i2][i3][i4];
            }
            FOR(i2,1,n-m+1)
                f3[i1][i2][i3][i4] = min(r[i2], l[i2+m-1]);
        }

        FOR(i2,1,n-m+1) FOR(i3,1,n-m+1) FOR(i4,1,n-m+1) {
            FOR(i1,1,n) {
                if (block[i1] == block[i1-1])
                    l[i1] = min(l[i1-1], f3[i1][i2][i3][i4]);
                else l[i1] = f3[i1][i2][i3][i4];
            }
            FORD(i1,n,1) {
                if (block[i1] == block[i1+1])
                    r[i1] = min(r[i1+1], f3[i1][i2][i3][i4]);
                else r[i1] = f3[i1][i2][i3][i4];
            }
            FOR(i1,1,n-m+1)
                f4[i1][i2][i3][i4] = min(r[i1], l[i1+m-1]);
        }

        n = n - m + 1;
        FOR(i1,1,n) FOR(i2,1,n) FOR(i3,1,n) FOR(i4,1,n) printf("%d ", f4[i1][i2][i3][i4]);
        puts("");
    }
    return 0;
}
