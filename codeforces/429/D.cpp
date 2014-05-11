#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

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
using namespace std;

const int MN = 100111;
const int oo = 2000111000;

int n, a[MN], sum[MN];

inline int fastMin(int x, int y) { return (((y-x)>>(32-1))&(x^y))^x; }

int main() {
    ios :: sync_with_stdio(false);
    GN(n);
    FOR(i,1,n) {
        GN(a[i]);
        sum[i] = sum[i-1] + a[i];
    }
    int res = oo;
    int minSum = res;
    FOR(i,2,n) {
        res = min(res, a[i]*a[i] + 1);
        minSum = min(minSum, abs(a[i]));
    }

    bool hasPositive = false, hasNegative = false;
    FOR(i,1,n)
        if (a[i] > 0) hasPositive = true;
        else if (a[i] < 0) hasNegative = true;

    if (hasPositive && hasNegative)
    FOR(len,2,n) {
        int ll = len*len;
        if (ll > res) break;

        minSum = oo;
        int curSum;
        FOR(i,len+1,n) {
            curSum = sum[i] - sum[i-len];
            if (curSum < 0) curSum = -curSum;
            minSum = fastMin(minSum, curSum);
        }
        if (minSum < 10000)
            res = fastMin(res, minSum*minSum + ll);
    }
    cout << res << endl;
    return 0;
}
