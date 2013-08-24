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

const int MN = 100111;

set<int> block[MN];
int m, n, x[MN];

int main() {
    // ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) block[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            block[u].insert(v);
            block[v].insert(u);
        }

        bool hasResult = false;
        REP(turn,10000) {
            FOR(i,1,n) {
                x[i] = i;
                swap(x[i], x[rand() % i + 1]);
            }

            x[n+1] = x[1];

            bool ok = true;
            FOR(i,1,m)
            if (block[x[i]].find(x[i+1]) != block[x[i]].end()) {
                ok = false;
                break;
            }

            if (ok) {
                hasResult = true;
                FOR(i,1,m) printf("%d %d\n", x[i], x[i+1]);
                break;
            }
        }

        if (!hasResult) puts("-1");
    }
    return 0;
}
