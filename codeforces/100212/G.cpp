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

int a[111], t[33][33], f[111][33], tr[111][33];
int l, m;

void trace(int i, int last) {
    if (i == 1) {
        putchar('a' + last - 1);
        return ;
    }
    trace(i-1, tr[i][last]);
    putchar('a' + last - 1);
}

int main() {
    freopen("ssh.in", "r", stdin);
    freopen("ssh.out", "w", stdout);
    
    while (cin >> l >> m) {
        FOR(i,1,l-1) cin >> a[i];
        FOR(i,1,m) FOR(j,1,m) cin >> t[i][j];

        FOR(i,1,l) FOR(j,1,m) f[i][j] = 1000111000;

        FOR(i,1,m) f[1][i] = 0;

        FOR(i,1,l-1) FOR(last,1,m) {
            FOR(next,1,m) {
                int cur = f[i][last] + abs(a[i] - t[last][next]);
                if (cur < f[i+1][next]) {
                    f[i+1][next] = cur;
                    tr[i+1][next] = last;
                }
            }
        }

        int res = 1000111000, save = -1;
        FOR(last,1,m)
            if (f[l][last] < res) {
                res = f[l][last];
                save = last;
            }
        trace(l, save);
        puts("");
    }
    return 0;
}