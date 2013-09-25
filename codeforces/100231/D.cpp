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

int n, A, B;
int x[20111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> A >> B && n) {
        memset(x, 0, sizeof x);
        
        int k = 0, res = 0;
        FOR(i,1,n) {
            int cnt, da, db;
            cin >> cnt >> da >> db;
            res += cnt * da;
            while (cnt--) x[++k] = db - da;
        }
        int nn = k - A, ln = min(B, k);
        if (nn < 0) nn = 0;

        sort(x+1, x+k+1);

        FOR(i,1,k) x[i] += x[i-1];

        int cur = res; res = 1000111000;
        FOR(i,nn,ln) {
            res = min(res, cur + x[i]);
        }

        // cout << nn << ' ' << ln << endl;
        cout << res << endl;
    }
    return 0;
}
