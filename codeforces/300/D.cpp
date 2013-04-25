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
const long long MOD = 7340033LL;

long long f[30][1011], g[30][1011];

long long get(long long n, int k) {
    long long res = 0;
    FOR(u,0,k) {
        int v = k - u;
        res = (res + g[n][u] * g[n][v]) % MOD;
    }
    return res;
}

int main() {
    // cout << "{\n";
    f[0][0] = 1;
    g[0][0] = 1;
    FOR(i,1,29) {
        // cout << "{";
        FOR(k,0,1000) {
            if (k == 0) {
                f[i][k] = 1;
                // cout << 1;
            }
            else {
                f[i][k] = get(i-1, k-1);
                // cout << ',' << f[i][k];
            }
        }

        FOR(k,0,1000) {
            FOR(x,0,k) {
                int y = k - x;
                g[i][k] = (g[i][k] + f[i][x] * f[i][y]) % MOD;
            }
        }
        // cout << "},\n";

        // cerr << i << endl;
    }
    // cout << "}\n";

    int q; scanf("%d", &q);
    while (q--) {
        int n, k; scanf("%d%d", &n, &k);

        int id = 0;
        while ((n - 1) % 2 == 0 && n >= 2) n = (n - 1) / 2, ++id;

        printf("%d\n", f[id][k]);
    }
    return 0;
}
