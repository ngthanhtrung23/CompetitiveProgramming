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

int k, n, maxb, t;
int b[100111];
int f[100111], bit[100111];

#define _(x) ((x) & (-(x)))

inline int get(register int u) {
    int res = 0;
    while (u > 0) {
        if (bit[u] > res) res = bit[u];
        u -= _(u);
    }
    return res;
}

inline void update(register int u, register int k) {
    while (u <= maxb) {
        if (k > bit[u]) bit[u] = k;
        u += _(u);
    }
}

void solve() {
    int res = 0;
    memset(f, 0, sizeof f);
    memset(bit, 0, sizeof bit);
    for(int turn = 1; turn <= t; ++turn) {
        for(int i = 1; i <= n; ++i) {
            int x = get(b[i] - 1) + 1;
            if (x > f[i]) {
                f[i] = x;
                update(b[i], x);
            }
        }
    }
    cout << *max_element(f+1, f+n+1) << endl;
}

int main() {
    while (scanf("%d%d%d%d", &k, &n, &maxb, &t) == 4) {
        while (k--) {
            FOR(i,1,n) scanf("%d", &b[i]);
            if (t >= maxb) {
                sort(b+1, b+n+1);
                cout << unique(b+1, b+n+1) - b - 1 << endl;
            }
            else {
                solve();
            }
        }
    }
    return 0;
}
