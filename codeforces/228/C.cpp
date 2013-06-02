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
const int MN = 511;

int m, n;
char board[MN][MN];
int sum[MN][MN];

bool check[MN][MN][10];

int getSum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}

bool good(int val, char c) {
    return (val == 0 && c == '.') || (val == 1 && c == '*');
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &board[i][1]);

        FOR(i,1,m) FOR(j,1,n) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + (board[i][j] == '*' ? 1 : 0);
        }

        int res = 0;
        REP(a,2) REP(b,2) REP(c,2) REP(d,2) {
            FOR(i,1,m-1) FOR(j,1,n-1) {
                check[i][j][1] = good(a, board[i][j])
                        && good(b, board[i][j+1])
                        && good(c, board[i+1][j])
                        && good(d, board[i+1][j+1]);
            }

            for(int t = 2, sz = 4; t <= 8; t++, sz <<= 1) {
                FOR(i,1,m-sz+1) FOR(j,1,n-sz+1) {
                    check[i][j][t] = true;

                    int small = (sz/2) * (sz/2);

                    if (a == 0) check[i][j][t] &= check[i][j][t-1];
                    else check[i][j][t] &= getSum(i, j, i+sz/2-1, j+sz/2-1) == small;

                    if (b == 0) check[i][j][t] &= check[i][j+sz/2][t-1];
                    else check[i][j][t] &= getSum(i, j+sz/2, i+sz/2-1, j+sz-1) == small;

                    if (c == 0) check[i][j][t] &= check[i+sz/2][j][t-1];
                    else check[i][j][t] &= getSum(i+sz/2, j, i+sz-1, j+sz/2-1) == small;

                    if (d == 0) check[i][j][t] &= check[i+sz/2][j+sz/2][t-1];
                    else check[i][j][t] &= getSum(i+sz/2, j+sz/2, i+sz-1, j+sz-1) == small;
                    
                    if (check[i][j][t]) ++res;
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}
