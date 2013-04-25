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

int n, m, c[55][55], deg[55], team[55], sz[55];
int first, last, qu[55];

void bfs(int u) {
    first = last = 1;
    qu[1] = u;
    while (first <= last) {
        u = qu[first++];
        FOR(v,1,n)
        if (!team[v] && c[u][v]) {
            team[v] = team[u];
            qu[++last] = v;
        }
    }
}

void solve() {
    FOR(i,1,n) if (deg[i] > 2) {
        puts("-1");
        return ;
    }
    int nTeam = 0;
    FOR(i,1,n) if (deg[i] > 0 && !team[i]) {
        ++nTeam; team[i] = nTeam;
        bfs(i);
        if (last > 3) {
            puts("-1");
            return ;
        }
        sz[nTeam] = last;
    }

    FOR(i,1,n) if (!team[i]) {
        FOR(t,1,nTeam)
        if (sz[t] < 3) {
            ++sz[t];
            team[i] = t;
            break;
        }

        if (!team[i]) {
            ++nTeam;
            team[i] = nTeam;
            sz[nTeam] = 1;
        }
    }

    if (nTeam > n / 3) {
        puts("-1");
        return ;
    }

    FOR(t,1,nTeam) {
        FOR(i,1,n) if (team[i] == t) {
            printf("%d ", i);
        }
        puts("");
    }
}

int main() {
    while (cin >> n >> m) {
        memset(c, 0, sizeof c);
        memset(deg, 0, sizeof deg);
        memset(team, 0, sizeof team);
        memset(sz, 0, sizeof sz);

        while (m--) {
            int u, v; cin >> u >> v;
            c[u][v] = c[v][u] = 1;
            deg[u]++; deg[v]++;
        }

        solve();
    }
    return 0;
}
