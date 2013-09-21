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

int n, x[100111], a, b, gh;
int uoc[1000111];
int bit[1000111];

inline void update(int u, int val) {
    for(int x = u; x <= gh; x += x & -x)
        bit[x] = min(bit[x], val);
}

inline int get(int u) {
    int res = 1000111000;
    for(int x = u; x > 0; x -= x & -x)
        res = min(res, bit[x]);
    return res;
}

int main() {
    GN(n);
    FOR(i,1,n) GN(x[i]);
    GN(a); GN(b);
    sort(x+1, x+n+1);
    n = unique(x+1, x+n+1) - x - 1;

    cin >> a >> b;
    if (a == b) {
        cout << 0 << endl;
        return 0;
    }

    memset(uoc, 0, sizeof uoc);
    FOR(i,1,n) {
        int u = (b / x[i]) * x[i]; if (u < b) u += x[i];
        while (u < a) {
            uoc[u-b] = x[i];
            u += x[i];
        }
    }

    gh = a - b;
    FOR(i,1,1000110) bit[i] = 1000111000;

    update(gh, 0);

    int ln, d;
    FORD(u,gh-1,0) {
        ln = u+1;
        if (uoc[u]) ln = max(ln, u+uoc[u]-1);

        if (ln > gh) ln = gh;
        d = get(ln) + 1;

        if (u != 0) update(u, d);
        else cout << d << endl;
    }
    return 0;
}
