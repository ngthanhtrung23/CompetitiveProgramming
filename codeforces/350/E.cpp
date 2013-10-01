#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

const int MN = 333;
int n, m, k, good[MN], c[MN][MN], d[MN][MN], ke[MN][MN], x[MN], bad;

#define add(u,v) { ke[u][v] = ke[v][u] = 1; ++has; cout << u << ' ' << v << endl; if (has == m) return ; }

void solve2() {
    int left = x[1];
    int has = 0;

    FOR(i,1,n)
    if (i != bad)
        add(i, bad);

    FOR(i,1,n) FOR(j,i+1,n)
    if (i != left && i != bad)
        if (j != left && j != bad)
            add(i, j);

    FOR(i,1,n)
    if (!good[i] && i != bad)
        add(left, i);
    // if (has != m) cout << ":-O\n";
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> k) {
        memset(good, false, sizeof good);
        FOR(i,1,k) cin >> x[i], good[x[i]] = true;
        if (k == n) {
            cout << -1 << endl;
            continue;
        }
        int gh;
        gh = (n-2) * (n-3) / 2 + n - 2 + n - k;

        if (m > gh || m < 2) {
            cout << -1 << endl;
            continue;
        }

        bad = 1;
        while (good[bad]) ++bad;

        memset(ke, 0, sizeof ke);

        solve2();
        continue;

        // Check
        FOR(i,1,n) FOR(j,1,n)
        if (i == j) c[i][j] = 0;
        else if (ke[i][j]) c[i][j] = c[j][i] = 1;
        else c[i][j] = 1000111000;

        FOR(i,1,n) FOR(j,1,n) d[i][j] = c[i][j];

        FOR(t,1,k) {
            int v = x[t];
            FOR(i,1,n) FOR(j,1,n)
                c[i][j] = min(c[i][j], c[i][v] + c[v][j]);
        }

        FOR(t,1,n) {
            FOR(i,1,n) FOR(j,1,n)
                d[i][j] = min(d[i][j], d[i][t] + d[t][j]);
        }

        bool ok = false;
        FOR(i,1,n) FOR(j,1,n)
            if (c[i][j] != d[i][j]) {
                ok = true;
            }
        if (!ok) cout << ":(\n";
    }
    return 0;
}
