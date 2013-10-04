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

int n, a[4011], b[4011];

int main() {
    while (scanf("%d", &n) == 1) {
        n *= 2;
        int sum = 0;
        FOR(i,1,n) {
            int x; scanf("%d.%d", &x, &a[i]);
            sum += a[i];
        }
        sort(a+1, a+n+1);

        FOR(i,1,n) if (a[i] == 0) b[i] = 0; else b[i] = 1000;
        sort(b+1, b+n+1);

        int res = 1<<29;

        int low = 0, high = 0;
        FOR(i,1,n/2) low += b[i], high += b[n/2+i];

        for(int i = low; i <= high; i += 1000)
            res = min(res, abs(sum - i));

        printf("%.3lf\n", res / 1000.0);
    }
    return 0;
}
