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

int n, a[111][111], row[111], x[111][111];

int main() {
    while (cin >> n && n) {
        memset(row, 0, sizeof row);
        memset(a, 0, sizeof a);
        FOR(i,1,n) {
            while (cin >> a[i][row[i]+1]) {
                if (a[i][row[i]+1] == 0) break;
                ++row[i];
            }
        }

        memset(x, 0, sizeof x);
        FOR(j,1,row[1]) {
            FOR(i,1,n) {
                if (!a[i][j]) break;

                FOR(t,1,a[i][j]) {
                    ++x[t][i];
                }
            }
        }
        for(int i = 1; i <= 100 && x[i][1]; ++i) {
            for(int j = 1; j <= 100 && x[i][j]; ++j) {
                cout << x[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;

        memset(x, 0, sizeof x);
        FOR(i,1,n) {
            FOR(j,1,row[i]) {
                FOR(t,1,a[i][j]) {
                    ++x[j][t];
                }
            }
        }
        for(int i = 1; i <= 100 && x[i][1]; ++i) {
            for(int j = 1; j <= 100 && x[i][j]; ++j) {
                cout << x[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}