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

int m, n, k;
char a[411][411];
int f[411][411], x[411], cnt[411][411];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d\n", &m, &n, &k) == 3) {
        FOR(i,1,m) {
            scanf("%s\n", &a[i][1]);
            FOR(j,1,n) {
                f[i][j] = f[i-1][j];
                if (a[i][j] == 'a') ++f[i][j];
            }
        }

        long long res = 0;
        FOR(i1,1,m) FOR(i2,i1+1,m) {
            FOR(j,1,n) x[j] = f[i2][j] - f[i1-1][j];

            FOR(j,1,n) {
                FOR(c,'a','z') cnt[c][j] = cnt[c][j-1];
                if (a[i1][j] == a[i2][j])
                    ++cnt[a[i1][j]][j];
            }

            int j2 = 0, cur = 0;
            FOR(j1,1,n) {
                cur -= x[j1-1];
                if (j2 < j1-1) j2 = j1-1;
                while (j2 < n && cur + x[j2+1] <= k) {
                    ++j2;
                    cur += x[j2];
                }

                if (j1 < j2 && a[i1][j1] == a[i2][j1])
                    res += cnt[a[i1][j1]][j2] - cnt[a[i1][j1]][j1];
            }
        }
        cout << res << endl;
    }
    return 0;
}
