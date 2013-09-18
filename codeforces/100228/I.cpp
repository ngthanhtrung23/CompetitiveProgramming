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

int n, m, a[111];
bool c[111][111], used[111];
long long f[111];

bool check(int i) {
    REP(j,i) if (!c[i][j] && !used[j]) return false;
    FOR(j,i+1,n-1) if (c[i][j] && !used[j]) return false;
    return true;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        memset(c, false, sizeof c);
        memset(used, false, sizeof used);

        while (m--) {
            int u, v; cin >> u >> v;
            c[u][v] = c[v][u] = true;
        }

        REP(num,n) { // Where to put num?
            int id = 0;
            while (used[id] || !check(id)) ++id;

            a[id] = num;
            used[id] = true;
        }

        // PR0(a, n);

        long long res = 0;
        REP(i,n) {
            f[i] = 0;
            bool ok = true;
            REP(j,i) if (a[j] < a[i]) ok = false;
            if (ok) f[i] = 1;

            int ln = -1;
            FORD(j,i-1,0) if (a[j] < a[i]) {
                if (a[j] < ln) continue;
                ln = max(ln, a[j]);

                f[i] += f[j];
            }

            ok = true;
            FOR(j,i+1,n-1) if (a[j] > a[i]) ok = false;
            if (ok) res += f[i];
        }
        // PR0(f, n);
        cout << res << endl;
    }
    return 0;
}
