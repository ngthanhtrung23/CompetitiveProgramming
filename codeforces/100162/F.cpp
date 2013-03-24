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
#include <ctime>

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

int n[2], m[2];
char a[2][511];
int f[511][511][2], tr[511][511][2], mark[511][511][2];
bool inq[511][511][2];
vector<int> ke[2][511];

queue< pair< pair<int,int>, int > > q;
vector<int> path1, path2;

int test = 0;

void init() {
    path1.clear(); path2.clear();

    memset(a, 0, sizeof a);
    REP(turn,2) {
        FOR(i,1,500) ke[turn][i].clear();
    }
    memset(f, -1, sizeof f);
    memset(tr, -1, sizeof tr);
    memset(mark, 0, sizeof mark);

    while (!q.empty()) q.pop();
}

void readInput(int turn) {
    scanf("%s\n", &a[turn][1]);
    FOR(i,1,m[turn]) {
        int u, v; scanf("%d%d", &u, &v);
        ke[turn][v].push_back(u);
    }
}

void insert(int i, int j, int turn) {
    // cout << "Add: " << i << ' ' << j << ' ' << turn << ' ' << f[i][j][turn] << endl;
    if (inq[i][j][turn]) return ;
    inq[i][j][turn] = true;

    q.push(make_pair(make_pair(i,j), turn));
}

void trace(int u, int v, int turn) {
    if (tr[u][v][turn] < 0) {
        path1.push_back(u);
        path2.push_back(v);
        return;
    }

    if (turn == 0) {
        trace(tr[u][v][turn], v, 1 - turn);
        path1.push_back(u);
    }
    else {
        trace(u, tr[u][v][turn], 1 - turn);
        path2.push_back(v);
    }
}

bool hasCycle;

int get(int u, int v, int turn) {
    if (hasCycle) return 0;

    if (f[u][v][turn] >= 0) return f[u][v][turn];

    mark[u][v][turn] = 1;

    int res = 1;
    if (turn == 0) {
        REP(i,ke[0][u].size()) {
            int uu = ke[0][u][i];

            if (mark[uu][v][1-turn] == 1) {
                hasCycle = true;
                return 0;
            }
            int t = get(uu, v, 1 - turn);

            if (t > res) {
                res = t;
                tr[u][v][turn] = uu;
            }
        }
    }
    else {
        REP(i,ke[1][v].size()) {
            int vv = ke[1][v][i];

            if (a[1][vv] != a[0][u]) continue;

            if (mark[u][vv][1-turn] == 1) {
                hasCycle = true;
                return 0;
            }

            int t = get(u, vv, 1 - turn) + 1;
            if (t > res) {
                res = t;
                tr[u][v][turn] = vv;
            }
        }
    }
    mark[u][v][turn] = 2;
    return f[u][v][turn] = res;
}

void solve() {
    hasCycle = false;
    FOR(i,1,n[0]) FOR(j,1,n[1])
    if (a[0][i] == a[1][j]) {
        if (f[i][j][0] == -1) {
            tr[i][j][0] = -1;
            f[i][j][0] = get(i, j, 0);

            if (hasCycle) {
                printf("Case %d: -1\n", ++test);
                return ;
            }
        }
    }

    int saveu = -1, savev = -1, res = 0;
    FOR(u,1,n[0]) FOR(v,1,n[1])
    if (f[u][v][0] > res) {
        res = f[u][v][0];
        saveu = u;
        savev = v;
    }

    if (res > 0) trace(saveu, savev, 0);

    printf("Case %d: ", ++test);
    printf("%d\n", res);
    REP(i,path1.size()) printf("%d ", path1[i]); puts("");
    REP(i,path2.size()) printf("%d ", path2[i]); puts("");
}

int main() {
    while (scanf("%d%d\n", &n[0], &m[0]) == 2) {
        init();

        readInput(0);
        scanf("%d%d\n", &n[1], &m[1]);
        readInput(1);

        solve();
    }
    return 0;
}
