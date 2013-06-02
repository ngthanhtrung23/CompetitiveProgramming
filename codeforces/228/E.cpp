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

int n, m;
int vertex[111], edge[111][111];
vector<int> ke[111];

bool dfs(int u) {
    REP(i,ke[u].size()) {
        int v = ke[u][i];

        if (vertex[v] == -1) {
            vertex[v] = 1 - (vertex[u] ^ edge[u][v]);
            bool cur = dfs(v);
            if (!cur) return false;
        }
        else {
            if (vertex[v] != 1 - (vertex[u] ^ edge[u][v]))
                return false;
        }
    }
    return true;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        memset(edge, -1, sizeof edge);
        memset(vertex, -1, sizeof vertex);

        while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
            scanf("%d", &edge[u][v]);
            edge[v][u] = edge[u][v];
        }

        bool ok = true;
        FOR(i,1,n) if (vertex[i] < 0) {
            vertex[i] = 0;
            if (dfs(i)) continue;

            vertex[i] = 1;
            if (!dfs(i)) {
                puts("Impossible");
                ok = false;
                break;
            }
        }
        if (ok) {
            int cnt = 0;
            FOR(i,1,n) cnt += vertex[i];
            printf("%d\n", cnt);
            FOR(i,1,n) if (vertex[i]) printf("%d ", i);
            puts("");
        }
    }
    return 0;
}
