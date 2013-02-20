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
const int MN = 1000111;

vector< int > a[MN];
int vao[MN];
vector< int > ke[MN];
int m, n;
pair<int,int> x[MN];
int res[MN], st[MN], top;

void init() {
    memset(vao, 0, sizeof vao);
    FOR(i,1,1000000) ke[i].clear();
}

void addEdge(int u, int v) {
    // cout << u << ' ' << v << endl;
    ke[u].PB(v);
    vao[v]++;
}

int main() {
    while (scanf("%d%d", &m, &n) == 2) {
        init();
        FOR(i,1,m) {
            a[i].resize(n+1);
            FOR(j,1,n) scanf("%d", &a[i][j]);
        }

        int id = n;
        FOR(i,1,m) {
            int k = 0;
            FOR(j,1,n)
            if (a[i][j] >= 0) {
                x[++k] = MP(a[i][j], j);
            }
            sort(x+1, x+k+1);

            int l = 1;
            // DEBUG(i);
            while (l <= k) {
                int r = l;
                while (r < k && x[l].F == x[r+1].F) ++r;

                if (l > 1) {
                    FOR(j,l,r) addEdge(id, x[j].S);
                }
                if (r < k) {
                    ++id;
                    FOR(j,l,r) addEdge(x[j].S, id);
                }
                l = r + 1;
            }
        }

        int k = 0;
        top = 0;
        FOR(i,1,id) {
            if (vao[i] == 0) {
                st[++top] = i;
            }
        }

        while (top) {
            int u = st[top--];
            res[++k] = u;
            REP(i,ke[u].size()) {
                int v = ke[u][i];
                vao[v]--;
                if (vao[v] == 0) st[++top] = v;
            }
        }

        if (k == id) {
            FOR(i,1,k)
                if (res[i] <= n) printf("%d ", res[i]);
            puts("");
        }
        else puts("-1");
    }
    return 0;
}
