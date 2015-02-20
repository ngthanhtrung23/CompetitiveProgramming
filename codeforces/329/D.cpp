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

int main() {
    int n, x;
    while (cin >> n >> x) {
        if (n == 5) {
            puts(">...v\nv.<..\n..^..\n>....\n..^.<\n1 1");
        }
        else if (n == 3) {
            puts(">vv\n^<.\n^.<\n1 3");
        }
        else {
            REP(turn,n/4) {
                REP(i,n/2) putchar('>');
                REP(i,n/4-1) {
                    putchar('.');
                    putchar('>');
                }
                putchar('.');
                puts("v");

                putchar('^');
                REP(i,n/4-1) {
                    putchar('.');
                    putchar('<');
                }
                putchar('.'); putchar('.');
                REP(i,n/2-1) putchar('<');
                puts("");

                putchar('v');
                REP(i,n/4-1) {
                    putchar('.');
                    putchar('<');
                }
                putchar('.');
                REP(i,n/2) putchar('<');
                puts("");

                REP(i,n/2-1) putchar('>');
                putchar('.');
                REP(i,n/4-1) {
                    putchar('.');
                    putchar('>');
                }
                putchar('.');
                putchar('^');
                puts("");
            }
            cout << 1 << ' ' << 1 << endl;
        }
    }
    return 0;
}