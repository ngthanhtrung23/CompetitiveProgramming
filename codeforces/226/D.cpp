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

int m, n, a[111][111], row[111], col[111], sum;
bool rrow[111], rcol[111];

void reverse(int i, int j) {
    row[i] -= a[i][j];
    col[j] -= a[i][j];
    sum -= a[i][j];

    a[i][j] = -a[i][j];

    row[i] += a[i][j];
    col[j] += a[i][j];
    sum += a[i][j];
}

bool check() {
    FOR(i,1,m) if (row[i] < 0) return false;
    FOR(j,1,n) if (col[j] < 0) return false;
    return true;
}

int main() {
    while (scanf("%d%d", &m, &n) == 2) {
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        sum = 0;
        FOR(i,1,m) FOR(j,1,n) {
            scanf("%d", &a[i][j]);
            row[i] += a[i][j];
            col[j] += a[i][j];
            sum += a[i][j];
        }

        memset(rrow, 0, sizeof rrow);
        memset(rcol, 0, sizeof rcol);

        while (!check()) {
            int nn = row[1];
            int ss = 0, si = 1;

            FOR(i,2,m) if (row[i] < nn) {
                nn = row[i];
                ss = 0; si = i;
            }

            FOR(j,1,n) if (col[j] < nn) {
                nn = col[j];
                ss = 1; si = j;
            }

            if (ss == 0) {
                rrow[si] = !rrow[si];
                FOR(j,1,n) {
                    reverse(si, j);
                }
            }
            else {
                rcol[si] = !rcol[si];
                FOR(i,1,m) {
                    reverse(i, si);
                }
            }
        }

        REP(turn,2) {
            int cnt = 0;
            FOR(i,1,m) if (rrow[i]) {
                if (!turn) ++cnt;
                else printf(" %d", i);
            }
            if (turn == 0) printf("%d", cnt);
            else puts("");
        }

        REP(turn,2) {
            int cnt = 0;
            FOR(j,1,n) if (rcol[j]) {
                if (!turn) ++cnt;
                else printf(" %d", j);
            }
            if (turn == 0) printf("%d", cnt);
            else puts("");
        }
    }
    return 0;
}
