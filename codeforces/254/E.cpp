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

int n, v, a[411];
int f[411][411], tr1[411][411], tr2[411][411];
vector< pair<int,int> > friends[411];

void update(int &a, int b) {
    if (a < 0) a = b;
    else a = max(a, b);
}

void trace(int n, int save) {
    if (n == 0) return ;
    int pn = tr1[n][save];
    int ps = tr2[n][save];

    trace(pn, ps);

    int add = f[n][save] - f[pn][ps];

    printf("%d", add);
    REP(i,add) printf(" %d", friends[n][i].S);

    puts("");
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d", &n, &v);
    FOR(i,1,n) scanf("%d", &a[i]);
    int m; scanf("%d", &m);
    FOR(i,1,m) {
        int l, r, f; scanf("%d%d%d", &l, &r, &f);
        FOR(d,l,r)
            friends[d].PB(MP(f, i));
    }

    FOR(i,1,n) {
        sort(friends[i].begin(), friends[i].end());
    }

    memset(f, -1, sizeof f);
    f[0][0] = 0;
    FOR(i,0,n-1) FOR(save,0,400) if (f[i][save] >= 0) {
        int sum = v;
        int has = save + a[i+1];
        int newSave = 0;

        if (has >= sum) {
            newSave = min(has - sum, a[i+1]);
            update(f[i+1][newSave], f[i][save]);

            if (f[i+1][newSave] == f[i][save]) {
                tr1[i+1][newSave] = i;
                tr2[i+1][newSave] = save;
            }
        }

        REP(x,friends[i+1].size()) {
            sum += friends[i+1][x].F;

            if (sum > has) break;

            newSave = min(has - sum, a[i+1]);

            update(f[i+1][newSave], f[i][save] + x+1);
            if (f[i+1][newSave] == f[i][save] + x + 1) {
                tr1[i+1][newSave] = i;
                tr2[i+1][newSave] = save;
            }
        }
    }

    int best = -1, save = 0;
    FOR(i,0,400) if (f[n][i] > best) {
        best = f[n][i];
        save = i;
    }
    printf("%d\n", best);
    trace(n, save);
    return 0;
}
