#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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

const int MN = 200111;

int n, p[MN], bit[MN];

#define _(x) ((x) & (-(x)))

void update(int u) {
    for(int x = u; x <= n+n; x += _(x))
        bit[x]++;
}

int get(int u) {
    int res = 0;
    for(int x = u; x > 0; x -= _(x))
        res += bit[x];
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            int u, v; cin >> u >> v;
            p[u] = v; p[v] = u;
        }

        long long res = n * (n-1LL) * (n-2) / 3;
        memset(bit, 0, sizeof bit);
        FOR(i,1,n+n) {
            if (p[i] > i) continue;

            int x = get(i) - get(p[i]);
            int z = (i-p[i]-1) - 2*x;
            long long y = n-1-x-z;

            res -= x*y*2 + z*(x+y);

            update(p[i]);
        }
        cout << res / 2 << endl;
    }
    return 0;
}
