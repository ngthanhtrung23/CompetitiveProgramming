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

const int MN = 200111;

pair<int,int> queries[MN];
int n, q, a[MN], cnt[MN], res[MN], id[MN];
vector<int> list[MN];

#define _(u) ((u) & (-(u)))

void update(int u) {
    while (u <= n) {
        cnt[u]++;
        u += _(u);
    }
}

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += cnt[u];
        u -= _(u);
    }
    return res;
}

void add(int i) {
    // Boi i
    int u = a[i] + a[i];
    while (u <= n) {
        if (id[u]) update(id[u]);
        u += a[i];
    }
    // Uoc i
    for(int t = 1; t * t <= a[i]; ++t)
        if (a[i] % t == 0) {
            if (id[t]) update(id[t]);
            if (t * t != a[i] && id[a[i] / t]) {
                update(id[a[i] / t]);
            }
        }
}

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            list[i].clear();
        }
        memset(cnt, 0, sizeof cnt);
        memset(id, 0, sizeof id);

        FOR(i,1,q) {
            scanf("%d%d", &queries[i].F, &queries[i].S);
            list[queries[i].F].PB(i);
        }

        FORD(i,n,1) {
            id[a[i]] = i;
            add(i);

            REP(t,list[i].size()) {
                int k = list[i][t];
                res[k] = get(queries[k].S);
            }
        }

        FOR(i,1,q) printf("%d\n", res[i]);
    }
    return 0;
}
