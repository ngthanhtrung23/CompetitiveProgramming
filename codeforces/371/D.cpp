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

const int MN = 200111;

int n, a[MN], next[MN], prev[MN], cur[MN];

int get(int u) {
    if (cur[next[u]] < a[next[u]]) return next[u];
    else return next[u] = get(next[u]);
}

void add(int u, int k) {
    if (u > n) return ;
    if (k == 0) return ;

    if (cur[u] + k < a[u]) {
        cur[u] += k;
    }
    else {
        k -= a[u] - cur[u];
        cur[u] = a[u];

        add(get(u), k);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i];
            cur[i] = 0;
        }
        FOR(i,0,n+1) next[i] = i+1, prev[i] = i-1;

        int q; cin >> q;
        a[n+1] = 1;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u, k; cin >> u >> k;
                add(u, k);
            }
            else if (typ == 2) {
                int u; cin >> u;
                cout << cur[u] << endl;
            }
        }
    }
    return 0;
}
