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

const int M = 55;
bool isRoot[M][M], hasLeft[M][M], hasUp[M][M];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n && n) {
        int x = 0;
        memset(isRoot, true, sizeof isRoot);
        memset(hasLeft, true, sizeof hasLeft);
        memset(hasUp, true, sizeof hasUp);

        FOR(i,1,n) {
            int k; cin >> k;
            int j = 0;
            FOR(turn,1,k) {
                ++j;
                while (!isRoot[i][j]) ++j;

                int nRow, nCol; cin >> nRow >> nCol;
                int i1 = i, i2 = i + nRow - 1;
                int j1 = j, j2 = j + nCol - 1;

                x = max(x, j2);

                FOR(ii,i1,i2) FOR(jj,j1,j2) {
                    if (ii != i1 || jj != j1) isRoot[ii][jj] = false;
                    if (ii != i1) hasUp[ii][jj] = false;
                    if (jj != j1) hasLeft[ii][jj] = false;
                }
            }
        }

        FOR(i,1,n) {
            FOR(j,1,x)
                if (hasUp[i][j]) printf(" --");
                else printf("   ");
            puts("");
            FOR(j,1,x) {
                if (hasLeft[i][j]) putchar('|');
                else putchar(' ');
                if (isRoot[i][j]) printf("%d%d", i, j);
                else printf("  ");
            }
            puts("|");
        }
        FOR(j,1,x) printf(" --");
        puts("");
        puts("");
    }
    return 0;
}
