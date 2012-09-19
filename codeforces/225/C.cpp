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
int INP,AM;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF, 0, sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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

int col[MN];
char tmp[MN];
int f[MN][2][MN];
int m, n, x, y;

void update(int &x, int k) {
    if (k < 0) return ;
    if (x < 0) x = k;
    else x = min(x, k);
}

int get(int color, int j) {
    if (color == 0) return col[j];
    else return m - col[j];
}

int main() {
    while (scanf("%d%d%d%d\n", &m, &n, &x, &y) == 4) {
        memset(col, 0, sizeof col);
        FOR(i,1,m) {
            scanf("%s\n", &tmp[1]);
            FOR(j,1,n) if (tmp[j] == '#') ++col[j];
        }

        memset(f, -1, sizeof f);

        f[1][0][1] = col[1];
        f[1][1][1] = m - col[1];

        FOR(i,1,n-1) REP(last,2) FOR(k,1,y) if (f[i][last][k] >= 0) {
            if (k >= x) {
                update(f[i+1][1-last][1], f[i][last][k] + get(1-last, i+1));
            }
            if (k < y) {
                update(f[i+1][last][k+1], f[i][last][k] + get(last, i+1));
            }
        }
        int res = -1;
        FOR(k,x,y) REP(last,2) {
            update(res, f[n][last][k]);
        }

        printf("%d\n", res);
    }
    return 0;
}
