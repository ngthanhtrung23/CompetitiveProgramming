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

const int MN = 1000111;
const int MOD = 1000000007;

int sum[MN];
int n, m, k;

#define _(x) ((x) & (-(x)))

void update(int u) {
    while (u <= n) {
        ++sum[u];
        u += _(u);
    }
}

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += sum[u];
        u -= _(u);
    }
    return res;
}

int p2[MN];

int main() {
    p2[0] = 1;
    FOR(i,1,1000000) p2[i] = (p2[i-1] * 2) % MOD;

    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        bool ok = true;
        memset(sum, 0, sizeof sum);

        while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            if (v == u+1) continue;
            if (v != u + k + 1 || get(u - k - 1)) {
                ok = false;
            }
            else {
                update(u);
            }
        }
        if (!ok) puts("0");
        else {
            int res = 1;
            int gh = n - k - 1;
            // DEBUG(gh);
            FOR(i,1,gh) if (get(i-1) == 0 && get(n) - get(i+k) == 0) {
                int j = min(gh, i + k);
                int can = (j-i) - (get(j) - get(i));
                res = (res + p2[can]) % MOD;
                if (get(i) - get(i-1) == 1) {
                    res = (res + MOD - 1) % MOD;
                }
            }
            cout << res << endl;
        }
    }
    return 0;
}
