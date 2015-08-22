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
int n, m, diam, f[MN], save[MN], f2[MN], save2[MN], g[MN];
bool good[MN];

void dfs1(int u, int fu) {
    if (good[u]) f[u] = 0;
    else f[u] = -1000111000;

    save[u] = save2[u] = -1;
    f2[u] = -1000111000;

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs1(v, u);
        int now = f[v] + 1;
        if (now > f[u]) {
            f2[u] = f[u];
            save2[u] = save[u];

            f[u] = now;
            save[u] = v;
        }
        else if (now > f2[u]) {
            f2[u] = now;
            save2[u] = v;
        }
    }
}

void dfs2(int u, int fu) {
    if (good[u]) g[u] = 0;
    else g[u] = -1000111000;

    if (fu != -1) {
        g[u] = max(g[u], g[fu] + 1);
        if (save[fu] != u)
            g[u] = max(g[u], f[fu] + 1);
        else g[u] = max(g[u], f2[fu] + 1);
    }

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs2(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> diam) {
        FOR(i,1,n) ke[i].clear();

        memset(good, false, sizeof good);
        FOR(i,1,m) {
            int u; cin >> u;
            good[u] = true;
        }

        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        dfs1(1, -1);
        dfs2(1, -1);

        int res = 0;
        FOR(i,1,n)
            if (f[i] <= diam && g[i] <= diam)
                ++res;
        cout << res << endl;

        // PR(f, n);
        // PR(g, n);
    }
    return 0;
}