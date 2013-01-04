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

int n, a[MN], c[MN], f1[MN], f2[MN], sl;
long long k;

#define _(x) ((x) & (-(x)))

void update(int f[], int u, int k) {
    f[u] += k;
    int v = u + _(u);
    if (v <= sl) update(f, v, k);
}

int get(int f[], int u) {
    if (u <= 0) return 0;
    return f[u] + get(f, u-_(u));
}

int main() {
    while (cin >> n >> k) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            c[i] = a[i];
        }
        sort(c+1, c+n+1);
        sl = unique(c+1, c+n+1) - c - 1;
        FOR(i,1,n) a[i] = lower_bound(c+1, c+sl+1, a[i]) - c;

        // PR(a, n);

        long long inv = 0;
        memset(f1, 0, sizeof f1);
        memset(f2, 0, sizeof f2);

        FORD(i,n,1) {
            inv += get(f2, a[i] - 1);
            update(f2, a[i], 1);
        }

        if (inv <= k) {
            cout << n * (n-1LL) / 2 << endl;
            continue;
        }

        int r = 2;
        long long res = 0;

        // DEBUG(inv);
        update(f2, a[1], -1);

        FOR(l,1,n) {
            if (l > 1) {
                inv += l - 1 - get(f1, a[l]);
                inv += get(f2, a[l] - 1);
            }
            update(f1, a[l], 1);

            while (r < n && inv > k) {
                inv -= l - get(f1, a[r]);
                inv -= get(f2, a[r] - 1);

                update(f2, a[r], -1);
                ++r;
            }

            if (inv <= k) {
                res += n - r + 1;
            }
        }
        cout << res << endl;
    }
    return 0;
}
