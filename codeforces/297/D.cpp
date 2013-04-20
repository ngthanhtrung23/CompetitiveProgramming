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

const int MN = 1011;

int m, n, k, a[MN][MN];
char ngang[MN][MN], doc[MN][MN];

int main() {
    while (scanf("%d%d%d\n", &m, &n, &k) == 3) {
        int cnt = 0, all = 0;
        FOR(i,1,m) {
            FOR(j,1,n-1) {
                scanf("%c", &ngang[i][j]);
                all++;
                if (ngang[i][j] == 'E') ++cnt;
            }
            scanf("\n");
            if (i < m)
                FOR(j,1,n) {
                    scanf("%c", &doc[i][j]);
                    ++all;
                    if (doc[i][j] == 'E') ++cnt;
                }
            scanf("\n");
        }
        if (cnt / all >= 3 / 4) {
        }
        if (k == 1) {
            if (4 * cnt >= 3 * all) {
                puts("YES");
                FOR(i,1,m) {
                    FOR(j,1,n) printf("1 ");
                    puts("");
                }
            }
            else puts("NO");
            continue;
        }
        if (m > n) {
            FOR(j,1,n) {
                a[1][j] = 1;
                FOR(i,2,m)
                    if (doc[i-1][j] == 'E') a[i][j] = a[i-1][j];
                    else a[i][j] = 3 - a[i-1][j];

                if (j > 1) {
                    int good = 0, bad = 0;
                    FOR(i,1,m) {
                        if (ngang[i][j-1] == 'E' && a[i][j] == a[i][j-1]) ++good;
                        if (ngang[i][j-1] == 'N' && a[i][j] != a[i][j-1]) ++good;
                    }
                    bad = m - good;
                    if (bad > good) {
                        FOR(i,1,m) a[i][j] = 3 - a[i][j];
                    }
                }
            }
        }
        else {
            FOR(i,1,m) {
                a[i][1] = 1;
                FOR(j,2,n)
                    if (ngang[i][j-1] == 'E') a[i][j] = a[i][j-1];
                    else a[i][j] = 3 - a[i][j-1];

                if (i > 1) {
                    int good = 0, bad = 0;
                    FOR(j,1,n) {
                        if (doc[i-1][j] == 'E' && a[i-1][j] == a[i][j]) ++good;
                        if (doc[i-1][j] == 'N' && a[i-1][j] != a[i][j]) ++good;
                    }
                    bad = n - good;
                    if (bad > good) {
                        FOR(j,1,n) a[i][j] = 3 - a[i][j];
                    }
                }
            }
        }
        puts("YES");
        FOR(i,1,m) {
            FOR(j,1,n) printf("%d ", a[i][j]);
            puts("");
        }
    }
    return 0;
}
