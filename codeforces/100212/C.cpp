#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
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

const int MN = 2011;

int n, a[MN], best[MN][MN];
long long f[MN][MN], sum[MN];
int l;
char cur[MN];

void trace(int i, int j) {
    if (i > j) return ;
    if (i == j) {
        cur[l] = 0;
        puts(cur);
        return ;
    }

    int k = best[i][j];
    cur[l++] = '0';
    trace(i, k);
    cur[l-1] = '1';
    trace(k+1, j);
    --l;
}

int main() {
    freopen("codes.in", "r", stdin);
    freopen("codes.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i], sum[i] = sum[i-1] + a[i];
        FORD(i,n,1) FOR(j,i,n) {
            if (i == j) {
                f[i][j] = 0;
                best[i][j] = i;
            }
            else {
                f[i][j] = 1000111000111000111LL;
                FOR(k,max(best[i][j-1],i),min(best[i+1][j],j-1)) {
                    long long now = f[i][k] + f[k+1][j];
                    if (now < f[i][j]) {
                        f[i][j] = now;
                        best[i][j] = k;
                    }
                }
                f[i][j] += sum[j] - sum[i-1];
            }
        }
        // FOR(i,1,n) {
        //     FOR(j,i,n) cout << f[i][j] << ' ';
        //     cout << endl;
        // }
        // DEBUG(f[1][n]);

        trace(1, n);
    }
    return 0;
}