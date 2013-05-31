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

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

int n, p, a[55];
long double f[55][55][55];

int main() {
    while (scanf("%d", &n) == 1) {
        int sum = 0;
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        scanf("%d", &p);
        if (sum <= p) {
            cout << n << endl;
            continue;
        }

        long double res = 0.0;
        FOR(u,1,n) { // uth person will be the 1st outside
            memset(f, 0, sizeof f);

            f[0][0][0] = 1;
            FOR(i,0,n-1) {
                FOR(sum,0,p) FOR(j,0,i) {
                    long double val = f[i][sum][j];

                    if (i + 1 == u) f[i+1][sum][j] += val / (n-i);
                    else {
                        int turn = 1 + i-j;
                        if (i >= u) --turn;
                        f[i+1][sum][j] += val / (n-i) * turn;
                        if (sum + a[i+1] <= p) f[i+1][sum+a[i+1]][j+1] += val / (n-i) * (j+1);
                    }
                }
            }

            FOR(sum,0,p) if (sum + a[u] > p) {
                FOR(i,0,n) {
                    long double now = f[n][sum][i];
                    res += now * i;
                }
            }
        }
        cout << (fixed) << setprecision(10) << res << endl;
    }
}
