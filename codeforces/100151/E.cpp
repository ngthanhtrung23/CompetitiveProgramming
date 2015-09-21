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

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

typedef pair< pair<int,int>, int > State;

char a[16][16], b[16][16];
bool ok[16][16];
int id[16][16], posu[16], posv[16];
int m, n, cnt;
queue< State > q;

int d[16][16][17000];

bool inside(int u, int v) {
    return u > 0 && u <= m && v > 0 && v <= n;
}

const int knighti[] = {-2,-2,-1,-1,1,1,2,2};
const int knightj[] = {-1,1,-2,2,-2,2,-1,1};
const int rooki[] = {-1,1,0,0};
const int rookj[] = {0,0,-1,1};
const int bishopi[] = {-1,-1,1,1};
const int bishopj[] = {-1,1,-1,1};

bool solve() {
    while (!q.empty()) {
        State cur = q.front(); q.pop();
        if (cur.S == 0) {
            printf("%d\n", d[cur.F.F][cur.F.S][cur.S]);
            return true;
        }

        FOR(i,1,m) FOR(j,1,n) {
            if (a[i][j] == '*' || a[i][j] == '.') b[i][j] = '.';
            else {
                if (CONTAIN(cur.S, id[i][j])) {
                    b[i][j] = a[i][j];
                }
                else b[i][j] = '.';
            }
        }

        memset(ok, true, sizeof ok);
        FOR(i,1,m) FOR(j,1,n) {
            if (b[i][j] == 'K') {
                REP(dir,8) {
                    int ii = i + knighti[dir], jj = j + knightj[dir];
                    if (inside(ii, jj)) ok[ii][jj] = false;
                }
            }
            else if (b[i][j] == 'R') {
                REP(dir,4) {
                    int ii = i + rooki[dir], jj = j + rookj[dir];
                    while (inside(ii, jj)) {
                        ok[ii][jj] = false;
                        if (b[ii][jj] != '.') break;

                        ii += rooki[dir], jj += rookj[dir];
                    }
                }
            }
            else if (b[i][j] == 'B') {
                REP(dir,4) {
                    int ii = i + bishopi[dir], jj = j + bishopj[dir];
                    while (inside(ii, jj)) {
                        ok[ii][jj] = false;
                        if (b[ii][jj] != '.') break;

                        ii += bishopi[dir], jj += bishopj[dir];
                    }
                }
            }
        }
        // cout << cur.F.F << ' ' << cur.F.S << ' ' << cur.S << "   " << d[cur.F.F][cur.F.S][cur.S] << endl;
        // FOR(i,1,m) {
        //     PR(b[i], n);
        // }
        // FOR(i,1,m) {
        //     PR(ok[i], n);
        // }

        FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
            State next = MP(MP(cur.F.F + di, cur.F.S + dj), cur.S);
            if (inside(next.F.F, next.F.S) && ok[next.F.F][next.F.S]) {
                int now = id[next.F.F][next.F.S];
                if (now >= 0 && CONTAIN(next.S, now)) {
                    next.S -= TWO(now);
                }

                if (d[next.F.F][next.F.S][next.S] < 0) {
                    d[next.F.F][next.F.S][next.S] = d[cur.F.F][cur.F.S][cur.S] + 1;
                    q.push(next);
                }
            }
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    while (scanf("%d%d\n", &m, &n) == 2) {
        while (!q.empty()) q.pop();
        cnt = 0;
        memset(id, -1, sizeof id);
        FOR(i,1,m) {
            scanf("%s\n", &a[i][1]);
            FOR(j,1,n) if (a[i][j] != '*' && a[i][j] != '.') {
                id[i][j] = cnt;
                posu[cnt] = i;
                posv[cnt] = j;
                ++cnt;
            }
        }

        memset(d, -1, sizeof d);
        FOR(i,1,m) FOR(j,1,n)
        if (a[i][j] == '*') {
            q.push(MP(MP(i, j), TWO(cnt)-1));
            d[i][j][TWO(cnt)-1] = 0;
        }
        if (!solve()) puts("-1");
    }
    return 0;
}