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
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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
const int MN = 1011;

int a[MN][MN], f2[MN][MN], f5[MN][MN], p2[MN][MN], p5[MN][MN];
int n;

inline int min(const int &a, const int &b) {
    return (a < b) ? a : b;
}

void solve() {
    FOR(x,1,n) f2[0][x] = f2[x][0] = f5[0][x] = f5[x][0] = 1000111000;
    f2[1][0] = f5[1][0] = 0;

    FOR(i,1,n) FOR(j,1,n) {
        p2[i][j] = p5[i][j] = 0;
        int u;
        u = a[i][j]; while (!(u&1)) u >>= 1, p2[i][j]++;
        u = a[i][j]; while (u % 5 == 0) u /= 5, p5[i][j]++;

        f2[i][j] = min(f2[i-1][j], f2[i][j-1]) + p2[i][j];
        f5[i][j] = min(f5[i-1][j], f5[i][j-1]) + p5[i][j];
    }
}

void printPath(int i, int j) {
    FOR(t,1,i-1) putchar('D');
    FOR(t,1,j-1) putchar('R');

    FOR(t,i,n-1) putchar('D');
    FOR(t,j,n-1) putchar('R');
}

void trace2(int i, int j) {
    if (i == 1 && j == 1) return ;
    if (f2[i][j] == f2[i-1][j] + p2[i][j]) {
        trace2(i-1, j);
        putchar('D');
    }
    else {
        trace2(i, j-1);
        putchar('R');
    }
}

void trace5(int i, int j) {
    if (i == 1 && j == 1) return ;
    if (f5[i][j] == f5[i-1][j] + p5[i][j]) {
        trace5(i-1, j);
        putchar('D');
    }
    else {
        trace5(i, j-1);
        putchar('R');
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        bool has0 = false;
        int zeroi = -1, zeroj = -1;
        FOR(i,1,n) FOR(j,1,n) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 0) has0 = true, zeroi = i, zeroj = j, a[i][j] = 10;
        }
        solve();
        if (has0 && f2[n][n] > 1 && f5[n][n] > 1) {
            puts("1");
            printPath(zeroi, zeroj);
        }
        else if (f2[n][n] < f5[n][n]) {
            printf("%d\n", f2[n][n]);
            trace2(n, n);
        }
        else {
            printf("%d\n", f5[n][n]);
            trace5(n, n);
        }
        puts("");
    }
    return 0;
}