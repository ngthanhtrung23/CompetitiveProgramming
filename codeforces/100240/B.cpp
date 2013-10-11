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

const int MN = 10111;

vector<int> ke[MN];
int m, n, mx[MN], my[MN];
bool seen[MN];

bool dfs(int u) {
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (seen[v]) continue;

        seen[v] = true;
        if (!my[v] || dfs(my[v])) {
            mx[u] = v;
            my[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> m >> n;
        memset(mx, 0, sizeof mx);
        memset(my, 0, sizeof my);

        FOR(i,1,m) {
            ke[i].clear();
            int a, b; cin >> a >> b;
            ke[i].push_back(a);
            ke[i].push_back(b);
        }

        bool ok = true;
        FOR(i,1,m) {
            memset(seen, false, sizeof seen);
            if (!dfs(i)) {
                ok = false;
                break;
            }
        }
        if (ok) puts("successful hashing");
        else puts("rehash necessary");
    }
    return 0;
}
