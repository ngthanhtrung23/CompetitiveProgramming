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

string key, cipher;
bool used[111];
char a[111][111];

int main() {
    // freopen("input.txt", "r", stdin);
    while (cin >> key) {
        if (key == "THEEND") break;
        cin >> cipher;

        int n = key.size();
        int m = cipher.size() / n;

        int cur = 0;
        memset(a, 0, sizeof a);

        memset(used, false, sizeof used);
        REP(turn,key.size()) {
            int id = -1;
            char c = 'Z' + 1;
            REP(i,key.size())
                if (key[i] < c && !used[i]) {
                    c = key[i];
                    id = i;
                }
            used[id] = true;

            REP(i,m) a[i][id] = cipher[cur++];
        }
        REP(i,m) REP(j,n) putchar(a[i][j]);
        puts("");
    }
    return 0;
}