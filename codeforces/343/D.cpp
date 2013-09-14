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

const int MN = 1000111;

vector<int> ke[MN];
int getIn[MN], getOut[MN], cnt;
int all[MN*3], empty[MN*3], maxEmpty[MN*3];

void dfs(int u, int fu) {
    getIn[u] = ++cnt;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs(v, u);
    }
    getOut[u] = cnt;
}

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void updateFill(int i, int l, int r, int u, int v, int t) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        all[i] = t;
        return ;
    }
    int mid = (l + r) >> 1;
    updateFill(CT(i), l, mid, u, v, t);
    updateFill(CP(i), mid+1, r, u, v, t);
}

void updateEmpty(int i, int l, int r, int u, int t) {
    if (u < l || r < u) return ;
    if (l == r) {
        empty[i] = maxEmpty[i] = t;
        return ;
    }
    int mid = (l + r) >> 1;
    updateEmpty(CT(i), l, mid, u, t);
    updateEmpty(CP(i), mid+1, r, u, t);
    maxEmpty[i] = max(maxEmpty[i], max(maxEmpty[CT(i)], maxEmpty[CP(i)]));
}

int getFill(int i, int l, int r, int u) {
    if (u < l || r < u) return 0;
    if (l == r) return all[i];
    if (all[i]) {
        all[CT(i)] = max(all[CT(i)], all[i]);
        all[CP(i)] = max(all[CP(i)], all[i]);
    }
    int mid = (l + r) >> 1;
    return max(getFill(CT(i), l, mid, u), getFill(CP(i), mid+1, r, u));
}

int getEmpty(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return maxEmpty[i];
    int mid = (l + r) >> 1;
    return max(getEmpty(CT(i), l, mid, u, v), getEmpty(CP(i), mid+1, r, u, v));
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();

        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        cnt = 0;
        dfs(1, -1);

        int q; cin >> q;
        memset(all, 0, sizeof all);
        memset(empty, 0, sizeof empty);
        memset(maxEmpty, 0, sizeof maxEmpty);

        FOR(i,1,q) {
            int type, u; cin >> type >> u;
            if (type == 1) {
                updateFill(1, 1, n, getIn[u], getOut[u], i);
            }
            else if (type == 2) {
                updateEmpty(1, 1, n, getIn[u], i);
            }
            else {
                int lastFill = getFill(1, 1, n, getIn[u]);
                int lastEmpty = getEmpty(1, 1, n, getIn[u], getOut[u]);
                if (lastFill <= lastEmpty) puts("0");
                else puts("1");
            }
        }
    }
    return 0;
}
