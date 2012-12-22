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
const long long MOD = 1000000007LL;

string ub;
long long f[100][2][100], g[100], choose[100][100][100], c[111][111];
int m, l;

long long get(long long ub, int u) {
    long long res = 1;
    REP(i,u)
        res = (res * (ub-i)) % MOD;
    return res;
}

void init() {
    stringstream ss; ss << m;
    ss >> ub; l = ub.length();
    ub = ' ' + ub;

    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    FOR(i,0,l-1) REP(t,2) FOR(u,0,i) if (f[i][t][u]) {
        FOR(cur,0,9)
        if (t == 1 || (cur <= ub[i+1] - '0')) {
            int tt = t;
            if (cur < ub[i+1] - '0') tt = 1;

            int uu = u;
            if (cur == 4 || cur == 7) ++uu;

            f[i+1][tt][uu] += f[i][t][u];
        }
    }

    FOR(i,0,l) {
        g[i] = f[l][1][i] % MOD;
    }
    g[0]--;
    // PR0(g, l+1);

    memset(c, 0, sizeof c);
    c[0][0] = 1;
    FOR(i,1,100) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = c[i-1][j-1] + c[i-1][j];
    }

    memset(choose, 0, sizeof choose);
    choose[0][0][l+1] = 1;

    FOR(i,0,5) FOR(sum,0,99) FOR(last,0,l+1)
    if (choose[i][sum][last]) {
        int bound = last+1;
        if (last == l+1) bound = 0;

        FOR(cur,bound,l) FOR(x,1,6) if (i+x <= 6) {
            choose[i+x][sum+cur*x][cur] += choose[i][sum][last] * get(g[cur], x) % MOD * c[i+x][x] % MOD;
            choose[i+x][sum+cur*x][cur] %= MOD;
        }
    }
}

int main() {
    while (scanf("%d", &m) == 1) {
        ++m;
        init();

        long long res = 0;
        FOR(i,1,l) {
            long long has = 0;
            FOR(j,0,i-1)
            FOR(last,0,l)
                has += choose[6][j][last];

            if (has < 6) continue;

            res = (res + g[i] * has) % MOD;
        }
        cout << res << endl;
    }

    // cout << (get(12, 1) * get(31, 5) * 6 % MOD + get(31, 6) % MOD + 12LL * get(31, 6)) % MOD << endl;
    return 0;
}
