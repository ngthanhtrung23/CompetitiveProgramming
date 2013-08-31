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

int a[1011][1011];

bool check() {
    FOR(i,1,6)
    FOR(j,1,6) if (i != j) {
        if (a[i][j]) continue;

        bool ok = false;
        FOR(k,1,6) if (i != k && j != k)
            if (a[i][k] && a[k][j]) {
                ok = true;
                break;
            }
        if (!ok) return false;
    }
    return true;
}

void solve(int n) {
    if (n == 3) {
        a[1][2] = a[2][3] = a[3][1] = 1;
        return ;
    }
    else if (n == 6) {
        REP(mask,1<<15) {
            int cur = 0;
            FOR(i,1,5) FOR(j,i+1,6) {
                if (mask & (1<<cur)) {
                    a[i][j] = 1;
                    a[j][i] = 0;
                }
                else {
                    a[i][j] = 0;
                    a[j][i] = 1;
                }
                cur++;
            }

            if (check()) return ;
        }
    }
    else {
        solve(n-2);
        a[n-1][n] = 1;
        FOR(i,1,n-2) a[i][n-1] = 1, a[n][i] = 1;
    }
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 4) puts("-1");
        else {
            memset(a, 0, sizeof a);
            solve(n);

            FOR(i,1,n) {
                FOR(j,1,n) printf("%d ", a[i][j]);
                puts("");
            }
        }
        puts("");
    }
    return 0;
}
