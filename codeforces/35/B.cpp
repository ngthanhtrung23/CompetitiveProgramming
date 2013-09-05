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

int m, n;
string s[33][33];

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    ios :: sync_with_stdio(false);
    int q;
    while (cin >> m >> n >> q) {
        FOR(i,1,m) FOR(j,1,n) s[i][j] = "";

        while (q--) {
            int type; cin >> type;
            if (type > 0) {
                int u, v; string cur;
                cin >> u >> v >> cur;
                bool found = false;
                for(int i = u; i <= m; ++i) {
                    for(int j = 1; j <= n; ++j) {
                        if (i > u || j >= v) {
                            if (s[i][j] == "") {
                                s[i][j] = cur;
                                found = true;
                                break;
                            }
                        }
                    }
                    if (found) break;
                }
            }
            else {
                string cur; cin >> cur;
                bool found = false;
                FOR(i,1,m) {
                    FOR(j,1,n)
                    if (s[i][j] == cur) {
                        cout << i << ' ' << j << endl;
                        found = true;
                        s[i][j] = "";
                        break;
                    }
                    if (found) break;
                }
                if (!found) cout << -1 << ' ' << -1 << endl;
            }
        }
    }
    return 0;
}
