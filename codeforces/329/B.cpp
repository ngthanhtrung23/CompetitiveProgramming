#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

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

const int MN = 1011;

int m, n;
char a[MN][MN];
int qu[MN*MN], qv[MN*MN], first, last, d[MN][MN];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

void bfs(int u, int v) {
    memset(d, -1, sizeof d);
    d[u][v] = 0;

    first = last = 1; qu[1] = u; qv[1] = v;
    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu > 0 && uu <= m && vv > 0 && vv <= n 
                    && a[uu][vv] != 'T' && d[uu][vv] < 0) {
                ++last; 
                qu[last] = uu; qv[last] = vv;
                d[uu][vv] = d[u][v] + 1;
            }
        }
    }
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        FOR(i,1,m) FOR(j,1,n)
        if (a[i][j] == 'E') bfs(i, j);

        int len = -1;
        FOR(i,1,m) FOR(j,1,n)
            if (a[i][j] == 'S') len = d[i][j];

        int res = 0;
        FOR(i,1,m) FOR(j,1,n)
            if (a[i][j] >= '0' && a[i][j] <= '9' && d[i][j] <= len && d[i][j] >= 0)
                res += (a[i][j] - '0');
        cout << res << endl;
    }
    return 0;
}
