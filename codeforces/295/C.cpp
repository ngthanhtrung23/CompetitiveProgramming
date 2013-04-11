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

long long c[55][55];
int f[55][55][2];
long long g[55][55][2];

int qu[55*55*2], qv[55*55*2], qt[55*55*2];
int n, k;

int main() {
    c[0][0] = 1;
    FOR(i,1,50) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
    }
    while (cin >> n >> k) {
        int cnt0 = 0, cnt1 = 0;
        FOR(i,1,n) {
            int a; cin >> a;
            if (a == 50) ++cnt0; else ++cnt1;
        }
        memset(f, -1, sizeof f); memset(g, 0, sizeof g);

        f[cnt0][cnt1][1] = 0;
        g[cnt0][cnt1][1] = 1;
        int first = 1, last = 1;
        qu[1] = cnt0, qv[1] = cnt1, qt[1] = 1;

        while (first <= last) {
            int u = qu[first], v = qv[first], t = qt[first]; ++first;

            if (t == 1) { // Dua nguoi sang song
                FOR(i,0,u) FOR(j,0,v)
                if (i || j) {
                    if (i * 50 + j * 100 <= k) {
                        if (f[u-i][v-j][0] < 0) {
                            f[u-i][v-j][0] = f[u][v][t] + 1;
                            g[u-i][v-j][0] = g[u][v][t] * c[u][i] % MOD * c[v][j] % MOD;
                            ++last;
                            qu[last] = u-i; qv[last] = v-j; qt[last] = 0;
                        }
                        else if (f[u-i][v-j][0] == f[u][v][t] + 1) {
                            g[u-i][v-j][0] = (g[u][v][t] * c[u][i] % MOD * c[v][j] % MOD + g[u-i][v-j][0]) % MOD;
                        }
                    }
                    else break;
                }
            }
            else { // Dua nguoi tro ve
                FOR(i,0,cnt0-u) FOR(j,0,cnt1-v)
                if (i || j) {
                    if (i * 50 + j * 100 <= k) {
                        if (f[u+i][v+j][1] < 0) {
                            f[u+i][v+j][1] = f[u][v][t] + 1;
                            g[u+i][v+j][1] = g[u][v][t] * c[cnt0-u][i] % MOD * c[cnt1-v][j] % MOD;
                            ++last;
                            qu[last] = u+i; qv[last] = v+j; qt[last] = 1;
                        }
                        else if (f[u+i][v+j][1] == f[u][v][t] + 1) {
                            g[u+i][v+j][1] = (g[u][v][t] * c[cnt0-u][i] % MOD * c[cnt1-v][j] % MOD + g[u+i][v+j][1]) % MOD;
                        }
                    }
                    else break;
                }
            }
        }

        cout << f[0][0][0] << endl << g[0][0][0] << endl;
    }
    return 0;
}
