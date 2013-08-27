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

const int MN = 4011;
const int oo = 1000111000;
int cost[MN][MN], f[888][MN], n, k;

inline int getCost(int i, int j) {
    return cost[j][j] - cost[j][i-1] - cost[i-1][j] + cost[i-1][i-1];
}

void compute(int d, int l, int r, int u, int v) {
    if (l > r) return ;

    int mid = (l + r) >> 1;
    f[d][mid] = oo;
    int savek = u;
    FOR(k,u,min(v, mid-1)) {
        int now = f[d-1][k] + getCost(k+1, mid);
        if (now < f[d][mid]) {
            f[d][mid] = now;
            savek = k;
        }
    }
    compute(d, l, mid-1, u, savek);
    compute(d, mid+1, r, savek, v);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) FOR(j,1,n) {
            cin >> cost[i][j];
            cost[i][j] = cost[i-1][j] + cost[i][j-1] - cost[i-1][j-1] + cost[i][j];
        }

        f[0][0] = 0;
        FOR(i,1,n) f[0][i] = oo;

        FOR(d,1,k) {
            compute(d, 1, n, 0, n);
            // PR(f[d], n);
        }
        cout << f[k][n] / 2 << endl;
    }
    return 0;
}
