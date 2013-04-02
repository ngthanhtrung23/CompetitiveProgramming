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

const int MN = 80111;

int n;
vector<int> ke[MN];
long long f[MN], g[MN], sz[MN], sqz[MN];

long long dfs(int u, int fu) {
    sz[u] = 1;
    f[u] = g[u] = 0;
    long long sum = 0;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs(v, u);
        sz[u] += sz[v];
        sum += sqz[v];
    }
    sqz[u] = sz[u] * (sz[u] - 1) / 2;

    // Case 1: no path cross u
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        // a, b, c, d in T(v)
        f[u] += f[v];

        // a, b in T(v');  c, d in T(v)
        f[u] += sqz[v] * (sum - sqz[v]);
    }

    // Case 2: one path ends at u
    FORD(i,ke[u].size()-1,0) {
        int v = ke[u][i];
        if (v == fu) continue;

        g[u] += sz[v] * (sum - sqz[v]) * 2;
        g[u] += g[v];
    }
    f[u] += g[u];

    long long sumAll = 0;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        g[u] += sqz[v] * 2;

        sumAll += sz[v] * (sz[u] - sz[v] - 1);
    }
    sumAll /= 2;

    // Case 3: one path cross u
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        f[u] += sqz[v] * (sumAll - sz[v] * (sz[u] - 1 - sz[v])) * 2;
        f[u] += g[v] * (sz[u] - 1 - sz[v]);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();

        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        dfs(1, -1);
        cout << f[1] << endl;

        // PR(f, n);
        // PR(g, n);
    }
    return 0;
}
