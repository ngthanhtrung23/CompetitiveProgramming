#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

int n, c, a[211];
double f[211][211], cost[211][211];

inline void update(double &a, double val) {
    a = min(a, val);
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> c; FOR(i,1,n) cin >> a[i];

        FOR(i,1,n) FOR(j,i+1,n) {
            cost[i][j] = 0;
            FOR(k,i+1,j-1) {
                double guess = a[i] + (a[j] - a[i]) * (k-i) / (double) (j - i);
                cost[i][j] += fabs(a[k] - guess);
            }
        }

        FOR(i,0,n) FOR(x,0,c) f[i][x] = 1e50;
        f[1][1] = 0;
        FOR(i,1,n-1) FOR(x,1,c) {
            FOR(next,i+1,n) {
                update(f[next][x+1], f[i][x] + cost[i][next]);
            }
        }
        cout << (fixed) << setprecision(4) << f[n][c] / (double) n << endl;
    }
    return 0;
}
