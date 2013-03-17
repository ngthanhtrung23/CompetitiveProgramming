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
const long long MOD = 1000000007;

int n, q;
long long t;
long long f[2][100111];
vector<int> ke[311];
int a[311];
int value[311];
bool visited[311];
bool found;

int get(int u, int h) {
    if (found) return 0;

    if (visited[u]) {
        found = true;
        return 0;
    }
    visited[u] = true;
    int res = a[u];
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        t -= a[v];
        res += get(v, h+1);
    }

    return res;
}

void add(long long &a, long long b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int main() {
    int tmp;
    while (scanf("%d%d%d", &n, &q, &tmp) == 3) {
        t = tmp;
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        FOR(i,1,n) ke[i].clear();
        found = false;

        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,q) {
            int b, c; scanf("%d%d", &b, &c);
            ke[c].push_back(b);
        }

        FOR(i,1,n) {
            memset(visited, false, sizeof visited);
            value[i] = get(i, 1);
        }
        if (found || t < 0) {
            puts("0");
            continue;
        }
        // DEBUG(t);
        // PR(value, n);

        f[0][0] = 1;
        int now = 0;
        FOR(i,1,n) {
            FOR(x,0,t)
                f[1-now][x] = f[now][x];

            FOR(x,0,t-value[i]) {
                add(f[1-now][x+value[i]], f[1-now][x]);
            }
            now = 1 - now;
        }
        cout << f[now][t] << endl;
    }
    return 0;
}
