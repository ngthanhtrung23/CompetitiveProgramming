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

int n;
char tmp[111];
string a[10111];
set<string> s;

int main() {
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        scanf("%d\n", &n);
        s.clear();
        bool good = true;
        FOR(i,1,n) {
            gets(tmp);
            a[i] = string(tmp);
            if (s.find(a[i]) != s.end()) good = false;
            s.insert(a[i]);
        }
        FOR(i,1,n) {
            REP(x,a[i].length() - 1) {
                string t = a[i].substr(0, x+1);
                if (s.find(t) != s.end()) {
                    good = false;
                    break;
                }
            }
            s.insert(a[i]);
            if (!good) break;
        }
        if (good) puts("YES"); else puts("NO");
    }
    return 0;
}