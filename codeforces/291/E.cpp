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

int n;
int next[MN];
vector<int> ke[MN];
char tmp[MN];
string t, s[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
}

void initKMP() {
    next[0] = -1; int j = -1;
    FOR(i,1,t.length()-1) {
        while (j >= 0 && t[i] != t[j+1]) j = next[j];
        if (t[i] == t[j+1]) ++j;
        next[i] = j;
    }
    // PR0(next, t.length());
}

int res;
void dfs(int u, int j) {
    REP(i,s[u].length()) {
        while (j >= 0 && s[u][i] != t[j+1]) j = next[j];
        if (s[u][i] == t[j+1]) ++j;
        if (j == t.length()-1) {
            ++res;
            j = next[j];

            // cout << u << ' ' << i << endl;
        }
    }

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        dfs(v, j);
    }
}

int main() {
    while (scanf("%d\n", &n) == 1) {
        init();
        FOR(v,2,n) {
            gets(tmp);
            istringstream sin(tmp);
            int u; sin >> u >> s[v];
            ke[u].push_back(v);
        }
        gets(tmp);
        t = string(tmp);
        initKMP();

        res = 0;
        dfs(1, -1);
        printf("%d\n", res);
    }
    return 0;
}
