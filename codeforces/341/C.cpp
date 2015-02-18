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

const long long MOD = 1000000007;
const int MN = 2011;

int n, a[MN], c[MN][MN];
long long gt[MN];
bool x[MN], y[MN];

int main() {
    ios :: sync_with_stdio(false);
    FOR(i,0,2000) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;

        if (i == 0) gt[i] = 1;
        else gt[i] = (gt[i-1] * i) % MOD;
    }
    while (cin >> n) {
        memset(x, true, sizeof x);
        memset(y, true, sizeof y);
        FOR(i,1,n) {
            cin >> a[i];
            if (a[i] >= 0) {
                x[i] = false;
                y[a[i]] = false;
            }
        }

        int cnt = 0, k = 0;
        FOR(i,1,n) {
            if (x[i] && y[i]) ++cnt;
            if (x[i]) ++k;
        }

        n = k;

        long long res = 0;
        FOR(x,0,cnt) {
            if (x % 2 == 0) {
                res = (res + c[cnt][x] * gt[n-x]) % MOD;
            }
            else {
                res = (res - c[cnt][x] * gt[n-x] + MOD * MOD) % MOD;
            }
            // cout << x << ' ' << res << endl;
        }
        cout << res << endl;
    }
    return 0;
}