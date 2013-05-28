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

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

vector<int> ke[MN];
int n;
int res[MN];
bool dead[MN];

bool exists(int u, int v) {
    REP(i,ke[u].size())
        if (ke[u][i] == v) return true;
    return false;
}

bool check(int v1, int v2, int v3) {
    memset(dead, false, sizeof dead);
    res[1] = v1; res[2] = v2; res[3] = v3;
    dead[v1] = dead[v2] = dead[v3] = true;

    FOR(i,4,n) {
        int u = res[i-1];
        res[i] = -1;
        REP(t,ke[u].size()) {
            int v = ke[u][t];
            if (dead[v]) continue;

            if (exists(res[i-2], v)) {
                res[i] = v;
                break;
            }
        }

        if (res[i] < 0) return false;
        dead[res[i]] = true;
    }
    res[n+1] = res[1]; res[n+2] = res[2];
    FOR(i,1,n) {
        if (!exists(res[i], res[i+1])) return false;
        if (!exists(res[i], res[i+2])) return false;
    }
    return true;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        memset(dead, false, sizeof dead);

        FOR(i,1,n+n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        bool bad = false;
        FOR(i,1,n) if (ke[i].size() != 4) {
            bad = true;
            break;
        }
        if (bad) {
            puts("-1");
            continue;
        }

        bool ok = false;
        REP(i,min((int)ke[1].size(),3)) {
            int cnt = 0, u = ke[1][i];
            REP(j,4) if (ke[u][j] != 1 && exists(1, ke[u][j])) {
                if (check(1, u, ke[u][j])) {
                    FOR(t,1,n) printf("%d ", res[t]);
                    puts("");
                    ok = true;
                    break;
                }
                ++cnt;
                if (cnt == 2) break;
            }
            if (ok) break;
        }
        if (!ok) puts("-1");
    }
}
