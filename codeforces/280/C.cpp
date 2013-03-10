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
const int MN = 100111;

int n, sz[MN];
vector<int> ke[MN];

void dfs(int u, int fu) {
    sz[u] = 0;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        dfs(v, u);
        sz[u] += sz[v] + 1;
    }
}

long double get(int u, int h, int fu) {
    long double res = sz[u] / (h + (long double) 1.0) / (h + (long double) 2.0);
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        res += get(v, h+1, u);
    }
    return res;
}

int main() {
    cout << (fixed) << setprecision(9);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();

        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(v); ke[v].PB(u);
        }

        dfs(1, -1);

        cout << n - get(1, 0, -1) << endl;
    }
    return 0;
}
