#include <bits/stdc++.h>

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

const int MN = 100111;
int n, a[MN];
long long f[MN], g[MN];
vector< int > ke[MN];

bool cmp(int u, int v) {
    if (f[u] != f[v]) return f[u] > f[v];
    if (g[u] != g[v]) return g[u] > g[v];
    return u < v;
}

void dfs(int u, int fu) {
    vector< int > id; id.clear();

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        dfs(v, u);

        id.push_back(v);
    }

    sort(id.begin(), id.end(), cmp);

    f[u] = 1; g[u] = a[u] - 1;
    int last = -1;

    REP(i,id.size()) {
        int v = id[i];

        if (g[u]) { // Can still go back to u
            last = i;
            // Go into v
            f[u] += f[v];

            // Go back to u
            f[u]++;
            g[u]--;
        }
    }
    REP(i,last+1) {
        int v = id[i];
        int can = min(g[u], g[v]);

        g[u] -= can;
        f[u] += 2 * can;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        int s; cin >> s;
        ++a[s];
        dfs(s, -1);

        // PR(f, n);
        // PR(g, n);

        cout << f[s] - 1 << endl;
    }
    return 0;
}
