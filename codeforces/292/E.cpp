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

struct Node {
    int start_a, start_b, time;
} it[MN * 6], cur;

int n, q, a[MN], b[MN];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void update(int i, int l, int r, int x, int u, int v, int t) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].start_a = x;
        it[i].start_b = u;
        it[i].time = t;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, x, u, v, t);
    update(CP(i), mid+1, r, x, u, v, t);
}

void get(int i, int l, int r, int x) {
    if (x < l || r < x) return ;
    if (l == r) {
        if (it[i].time > cur.time) cur = it[i];
        return ;
    }

    if (it[i].time > cur.time) cur = it[i];

    int mid = (l + r) >> 1;
    get(CT(i), l, mid, x);
    get(CP(i), mid+1, r, x);
}

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,n) scanf("%d", &b[i]);
        memset(it, 0, sizeof it);

        FOR(i,1,q) {
            int type; scanf("%d", &type);
            if (type == 1) {
                int x, y, k; scanf("%d%d%d", &x, &y, &k);
                update(1, 1, n, x, y, y+k-1, i);
            }
            else {
                cur.time = 0;
                int x; scanf("%d", &x);
                get(1, 1, n, x);
                if (cur.time == 0) printf("%d\n", b[x]);
                else printf("%d\n", a[cur.start_a + x - cur.start_b]);
            }
        }
    }
    return 0;
}
