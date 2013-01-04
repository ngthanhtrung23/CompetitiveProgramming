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

const int MN = 100111;

const int MOD = 777777777;

int n, q;
int good[11][11];
int it[MN * 3][3][3];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void cal(int i) {
    REP(x,3) REP(y,3) {
        it[i][x][y] = 0;
        REP(m1,3) REP(m2,3) if (good[m1][m2])
            it[i][x][y] = (it[i][x][y] + it[CT(i)][x][m1] * (ll) it[CP(i)][m2][y]) % MOD;
    }
}

void init(int i, int l, int r) {
    if (l == r) {
        REP(t,3) it[i][t][t] = 1;
        // print(i, l, r);
        return ;
    }
    int mid = (l + r) >> 1;
    init(CT(i), l, mid);
    init(CP(i), mid+1, r);

    cal(i);
    // print(i, l, r);
}

void update(int i, int l, int r, int u, int k) {
    if (u < l || r < u) return ;
    if (l == r) {
        if (k == 0) {
            REP(t,3) it[i][t][t] = 1;
        }
        else {
            REP(t,3) {
                if (t == k-1) it[i][t][t] = 1;
                else it[i][t][t] = 0;
            }
        }
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, k);
    update(CP(i), mid+1, r, u, k);

    cal(i);
}

int main() {
    scanf("%d%d", &n, &q);
    REP(i,3) REP(j,3) scanf("%d", &good[i][j]);
    init(1,1,n);

    while (q--) {
        int u, k;
        scanf("%d%d", &u, &k);

        update(1,1,n,u,k);

        int res = 0;
        REP(x,3) REP(y,3)
            res = (res + it[1][x][y]) % MOD;
        printf("%d\n", res);
    }
    return 0;
}
