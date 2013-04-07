#define _GLIBCXX_DEBUG
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
const int MN = 5011;

int n;
long long res;
vector< pair<int,int> > ke[MN];
long long sz[MN], f[MN], g[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
}

void dfs1(int u, int block, int prev, vector<int> &cur) {
    sz[u] = 1;
    f[u] = 0;

    cur.push_back(u);
    REP(i,ke[u].size()) {
        int v = ke[u][i].first;
        int c = ke[u][i].second;
        if (v == block) continue;

        dfs1(v, u, c, cur);

        sz[u] += sz[v];
        f[u] += f[v] + c * sz[v] * (n - sz[v]);
    }
}

void dfs2(int u, int block, int prev, int other) {
    g[u] = 0;
    if (prev > 0) {
        int fu = block;
        g[u] = g[fu] + f[fu] - f[u] - prev * sz[u] * (n - sz[u]);
        g[u] += prev * (sz[u] + other) * (n - sz[u] - other);
    }
    REP(i,ke[u].size()) {
        int v = ke[u][i].first;
        int c = ke[u][i].second;
        if (v == block) continue;

        dfs2(v, u, c, other);
    }
}

const long long oo = 1000111000111000111LL;

int main() {
    while (scanf("%d", &n) == 1) {
        init();
        FOR(i,2,n) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        res = oo;

        vector<int> cur1, cur2;
        FOR(u,1,n)
        REP(i,ke[u].size()) {
            int v = ke[u][i].first;
            int c = ke[u][i].second;

            if (u > v) continue;

            // Try to remove add (u, v)
            cur1.clear(); cur2.clear();
            dfs1(u, v, -1, cur1);
            dfs1(v, u, -1, cur2);

            dfs2(u, v, -1, cur2.size());
            dfs2(v, u, -1, cur1.size());

            // cout << u << ' ' << v << endl;
            // PR0(cur1, cur1.size());
            // PR0(cur2, cur2.size());

            long long f1 = oo, f2 = oo;
            REP(t,cur1.size()) {
                int u = cur1[t];
                f1 = min(f1, f[u] + g[u]);
            }
            REP(t,cur2.size()) {
                int u = cur2[t];
                f2 = min(f2, f[u] + g[u]);
            }

            // cout << u << ' ' << v << endl;
            // PR(f, n);
            // PR(g, n);
            // DEBUG(f1);
            // DEBUG(f2);
            // DEBUG(c * sz[u] * sz[v]);

            res = min(res, f1 + f2 + c * sz[u] * sz[v]);
        }
        // DEBUG(res);
        cout << res << endl;
    }
    return 0;
}
