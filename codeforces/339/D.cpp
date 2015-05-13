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

const int MN = (1<<17) + 11;

int a[MN], m, n, val[MN * 4], op[MN * 4];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void build(int i, int l, int r) {
    if (r == l) {
        val[i] = a[l];
        op[i] = 1;
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    if (op[CT(i)] == 0) val[i] = val[CT(i)] ^ val[CP(i)];
    else val[i] = val[CT(i)] | val[CP(i)];
    op[i] = 1 - op[CT(i)];
}

void update(int i, int l, int r, int u, int k) {
    if (u < l || r < u) return ;

    if (l == r) {
        val[i] = k;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, k);
    update(CP(i), mid+1, r, u, k);

    if (op[CT(i)] == 0) val[i] = val[CT(i)] ^ val[CP(i)];
    else val[i] = val[CT(i)] | val[CP(i)];
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        n = 1<<n;
        FOR(i,1,n) cin >> a[i];
        build(1, 1, n);

        while (m--) {
            int u, v; cin >> u >> v;
            update(1, 1, n, u, v);
            cout << val[1] << endl;
        }
    }
    return 0;
}