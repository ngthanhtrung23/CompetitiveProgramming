#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
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

const int MN = 3011;
int n;
double c[MN][MN], x[MN], y[MN], y2[MN], x2[MN], x2_new[MN];

int main() {
    GN(n);
    memset(x, 0, sizeof x);
    REP(i,n) REP(j,n) {
        int t; GN(t);
        c[i][j] = t;
        x[i] += c[i][j];
    }
    REP(i,n) {
        int t; GN(t);
        y[i] = t;

        x[i] += y[i];
    }
    REP(i,n) {
        int t; GN(t);
        y2[i] = t;
    }

    REP(i,n) x2[i] = x[i];

    REP(i,n) REP(j,n) c[i][j] /= x[j];

    REP(turn,7) {
        memset(x2_new, 0, sizeof x2_new);
        REP(i,n) REP(j,n) {
            x2_new[i] += c[i][j] * x2[j];
        }
        REP(i,n) x2[i] = x2_new[i] + y2[i];
    }
    cout << (fixed) << setprecision(9);
    REP(i,n) cout << x2[i] << ' '; cout << endl;
}
