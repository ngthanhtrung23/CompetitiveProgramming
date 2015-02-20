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

const int MN = 50111;
vector<int> ke[MN];
int father[MN];

void dfs(int u, int fu) {
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        father[v] = u;
        dfs(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int n, r1, r2;
    while (cin >> n >> r1 >> r2) {
        FOR(i,1,n) ke[i].clear();
        
        FOR(i,1,n) if (i != r1) {
            int pi; cin >> pi;
            ke[i].push_back(pi);
            ke[pi].push_back(i);
        }
        dfs(r2, -1);
        FOR(i,1,n) if (i != r2) cout << father[i] << ' ';
        cout << endl;
    }
    return 0;
}