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

char a[2][50111];
int len[2];

int main() {
    while (gets(a[0])) {
        len[0] = strlen(a[0]);
        int t = 0;
        for(int rep = 1; rep + rep <= len[t]; ++rep) {
            t ^= 1; len[t] = 0;
            int cnt = 0, i;
            for(i = 0; i+rep < len[t^1]; ++i) {
                a[t][len[t]++] = a[t^1][i];
                cnt = (a[t^1][i] == a[t^1][i+rep]) ? cnt+1 : 0;
                if (cnt == rep) len[t] -= rep, cnt = 0;
            }
            for(; i < len[t^1]; ++i)
                a[t][len[t]++] = a[t^1][i];
            a[t][len[t]] = 0;
        }
        puts(a[t]);
    }
    return 0;
}
