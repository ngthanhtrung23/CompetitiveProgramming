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
const int MN = 300111;

int n, m;
vector<int> ke[MN];
int color[MN], bad[MN];
bool inq[MN];
queue<int> q;

void check(int u) {
    if (bad[u] > 1 && !inq[u]) {
        inq[u] = true;
        q.push(u);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) color[i] = 0;
        memset(inq, false, sizeof inq);
        while (!q.empty()) q.pop();

        while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(v);
            ke[v].PB(u);
            bad[u]++;
            bad[v]++;

            check(u); check(v);
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = false;
            if (bad[u] < 2) continue;

            color[u] = 1 - color[u];
            bad[u] = 0;
            REP(i,ke[u].size()) {
                int v = ke[u][i];
                if (color[v] == color[u]) {
                    ++bad[u];
                    ++bad[v];
                    check(v);
                }
                else {
                    --bad[v];
                }
            }
        }

        FOR(i,1,n) printf("%d", color[i]);
        puts("");
    }
    return 0;
}
