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
const int MN = 511;

int m, n;
char a[2][MN][MN];
int qu[MN * MN], qv[MN * MN], first, last;
bool visited[MN][MN];
int d[2][2][MN][MN];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

void bfs(int turn, int startu, int startv, int x) {
    memset(visited, false, sizeof visited);
    memset(d[turn][x], -1, sizeof d[turn][x]);

    first = last = 1;
    qu[1] = startu; qv[1] = startv;
    visited[startu][startv] = true;
    d[turn][x][startu][startv] = 0;

    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 1 || uu > m || vv < 1 || vv > n) continue;
            if (a[turn][uu][vv] == '#') continue;
            if (visited[uu][vv]) continue;

            visited[uu][vv] = true;
            d[turn][x][uu][vv] = d[turn][x][u][v] + 1;
            ++last;
            qu[last] = uu; qv[last] = vv;
        }
    }
}

bool check() {
    memset(visited, false, sizeof visited);
    first = last = 1; qu[1] = 1; qv[1] = 1; visited[1][1] = true;
    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;
        if (u == m && v == n) return true;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 1 || uu > m || vv < 1 || vv > n) continue;
            if (a[0][uu][vv] == '#' || a[1][uu][vv] == '#') continue;
            if (visited[uu][vv]) continue;

            if (d[0][0][uu][vv] != d[1][0][uu][vv] 
                || d[0][0][uu][vv] != d[0][0][u][v] + 1
                || d[1][0][uu][vv] != d[1][0][u][v] + 1
                || d[0][1][uu][vv] != d[1][1][uu][vv]
                || d[0][0][uu][vv] + d[0][1][uu][vv] != d[0][0][m][n]
                || d[1][0][uu][vv] + d[1][1][uu][vv] != d[1][0][m][n]) continue;

            ++last; qu[last] = uu; qv[last] = vv;
            visited[uu][vv] = true;
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        REP(turn,2) {
            FOR(i,1,m) scanf("%s\n", &a[turn][i][1]);
        }
        bfs(0, 1, 1, 0);
        bfs(0, m, n, 1);
        bfs(1, 1, 1, 0);
        bfs(1, m, n, 1);

        if (d[0][0][m][n] == -1 || d[1][0][m][n] == -1 || d[0][0][m][n] != d[1][0][m][n]) {
            puts("NO");
            continue;
        }

        if (check()) puts("YES");
        else puts("NO");
    }
    return 0;
}
