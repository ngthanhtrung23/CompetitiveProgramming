#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
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

const long double PI = acos((long double) -1.0);
const int MN = 3011;

vector< pair<int,int> > ke[MN];
int f[MN], g[MN], st[MN], top, trace[MN];
int n;

void resetAll() {
    top = 0;
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    FOR(i,1,n) ke[i].clear();
}

void dfs1(int u, int fu) {
    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;

        dfs1(v, u);
        f[u] += f[v] + ke[u][i].S;
    }
}

void dfs2(int u, int fu, int backEdge) {
    if (fu == -1) {
        g[u] = 0;
    }
    else {
        g[u] = g[fu] + f[fu] - f[u];
        if (backEdge == 0) ++g[u];
        else --g[u];
    }

    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;
        dfs2(v, u, ke[u][i].S);
    }
}

int prevEdge[MN], path[MN];

void dfs3(int u, int fu) {
    st[++top] = u;
    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;

        trace[v] = u;
        prevEdge[v] = ke[u][i].S;
        dfs3(v, u);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        resetAll();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(MP(v,0));
            ke[v].PB(MP(u,1));
        }
        dfs1(1, -1);
        dfs2(1, -1, 0);

        // PR(f, n);
        // PR(st, n);
        // PR(g, n);

        int best = n-1;
        FOR(u,1,n) {
            best = min(best, f[u] + g[u]);
            top = 0;
            dfs3(u, -1);

            path[u] = 0;
            FOR(i,2,n) {
                int v = st[i];

                if (prevEdge[v] == 0) {
                    path[v] = max(0, path[trace[v]] - 1);
                }
                else {
                    path[v] = path[trace[v]] + 1;
                }

                int now = f[u] + g[u] - path[v];

                best = min(best, now);
            }
        }
        
        cout << best << endl;
    }
    return 0;
}
