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

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

int n;
int ke[22];

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        memset(ke, 0, sizeof ke);

        REP(i,n) {
            int k; cin >> k;
            while (k--) {
                int u; cin >> u; --u;
                ke[i] |= TWO(u);
            }
        }

        int res = n;
        REP(mask,TWO(n)) {
            int cur = __builtin_popcount(mask);
            if (cur >= res) continue;

            int covered = mask;
            for(int i = 0; i < n; ++i)
                if (CONTAIN(mask,i))
                    covered |= ke[i];

            if (covered != TWO(n) - 1) continue;

            res = cur;
        }
        cout << res << "\n";
    }
    return 0;
}
