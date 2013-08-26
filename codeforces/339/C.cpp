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

string s;
int m;
bool f[1011][22][22];
pair<int,int> tr[1011][22][22];

void trace(int m, int a, int b) {
    if (m == 0) return ;
    trace(m-1, tr[m][a][b].first, tr[m][a][b].second);
    printf("%d ", b);
}

int main() {
    while (cin >> s) {
        cin >> m;
        memset(f, false, sizeof f);

        f[0][0][0] = true;
        FOR(move,0,m-1) FOR(diff,0,9) FOR(last,0,10)
        if (f[move][diff][last])
            FOR(cur,1,10)
            if (s[cur-1] == '1' && cur != last && cur > diff) {
                f[move+1][cur - diff][cur] = true;
                tr[move+1][cur - diff][cur] = make_pair(diff, last);
            }

        bool found = false;
        FOR(diff,0,10) FOR(last,0,10) {
            if (f[m][diff][last]) {
                puts("YES");
                trace(m, diff, last);
                puts("");
                found = true;
                break;
            }
            if (found) break;
        }
        if (!found) puts("NO");
    }
    return 0;
}
