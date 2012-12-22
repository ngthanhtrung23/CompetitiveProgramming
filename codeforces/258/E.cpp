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
const int MN = 200111;

int n, q, now, getIn[MN], getOut[MN], sl[MN * 8], sum[MN * 8], res[MN];
vector< int > ke[MN];
vector< pair<int,int> > queries[MN];

void init() {
    FOR(i,1,n) {
        ke[i].clear();
        queries[i].clear();
    }
    now = 0;

    memset(sum, 0, sizeof sum);
    memset(sl, 0, sizeof sl);
}

void dfs1(int u, int fu) {
    getIn[u] = ++now;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs1(v, u);
    }
    getOut[u] = now;
}

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void update(int i, int l, int r, int u, int v, int k) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        sl[i] += k;
        if (sl[i] > 0) sum[i] = r - l + 1;
        else sum[i] = sum[CT(i)] + sum[CP(i)];
        return ;
    }
    int mid = (l + r) >> 1;

    update(CT(i), l, mid, u, v, k);
    update(CP(i), mid+1, r, u, v, k);

    if (sl[i] == 0) sum[i] = sum[CT(i)] + sum[CP(i)];
    else sum[i] = r - l + 1;
}

void dfs2(int u, int fu) {
    REP(i,queries[u].size()) {
        int v = queries[u][i].F, w = queries[u][i].S;
        update(1, 1, n, getIn[v], getOut[v], +1);
        if (w != v) update(1, 1, n, getIn[w], getOut[w], +1);
    }

    res[u] = sum[1];
    if (res[u]) --res[u];

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs2(v, u);
    }

    REP(i,queries[u].size()) {
        int v = queries[u][i].F, w = queries[u][i].S;
        update(1, 1, n, getIn[v], getOut[v], -1);
        if (w != v) update(1, 1, n, getIn[w], getOut[w], -1);
    }
}

bool isAncestor(int u, int v) {
    return getIn[u] < getIn[v] && getOut[v] <= getOut[u];
}

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        init();

        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(v);
            ke[v].PB(u);
        }
        dfs1(1, -1);

        while (q--) {
            int a, b; scanf("%d%d", &a, &b);
            if (isAncestor(a, b)) {
                queries[a].PB(MP(a,a));
            }
            else if (isAncestor(b, a)) {
                queries[b].PB(MP(b,b));
            }
            else {
                queries[a].PB(MP(a,b));
                queries[b].PB(MP(a,b));
            }
        }

        dfs2(1, -1);

        FOR(i,1,n) printf("%d ", res[i]); puts("");
    }
    return 0;
}
