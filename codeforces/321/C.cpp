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

const int MN = 100111;
vector<int> ke[MN];
bool block[MN];
int color[MN], len[MN], tr[MN];
int n;

void dfs(int u, int fu, int &last) {
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu || block[v]) continue;

        len[v] = len[u] + 1;
        tr[v] = u;
        dfs(v, u, last);
        if (len[v] > len[last]) {
            last = v;
        }
    }
}

void solve(int root, int c) {
    len[root] = 0;
    tr[root] = root;
    int last = root;
    dfs(root, -1, last);

    len[last] = 0;
    dfs(last, -1, last);

    int l = len[last];
    REP(turn,l/2) last = tr[last];

    color[last] = c;
    block[last] = true;

    REP(i,ke[last].size()) {
        int u = ke[last][i];
        if (!block[u]) {
            solve(u, c+1);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        memset(block, false, sizeof block);

        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        solve(1, 0);

        FOR(i,1,n) {
            printf("%c ", color[i] + 'A');
        }
        puts("");
    }
    return 0;
}
