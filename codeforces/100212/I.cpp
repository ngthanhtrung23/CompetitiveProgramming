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

int m, n, p, flow;
int fl[666][666], c[666][666];
int qu[666], first, last, start, target, tr[666];
vector<int> ke[666];
pair<int,int> edges[333*333];

inline void addEdge(int u, int v) {
    ke[u].push_back(v);
    ke[v].push_back(u);
}

inline void addFlow(int u, int v) {
    fl[u][v]++;
    fl[v][u]--;
}

bool check() {
    FOR(i,1,m) if (fl[start][i] < 2) return false;
    FOR(i,m+1,m+n) if (fl[i][target] < 2) return false;
    return true;
}

bool findPath() {
    first = last = 1; qu[1] = start;
    memset(tr, 0, sizeof tr);
    tr[start] = start;

    while (first <= last) {
        int u = qu[first++];
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (!tr[v] && fl[u][v] > c[u][v]) {
                qu[++last] = v;
                tr[v] = u;
                if (v == target) return true;
            }
        }
    }
    return false;
}

void decFlow() {
    --flow;
    int v = target;
    while (v != start) {
        int u = tr[v];
        fl[u][v]--;
        fl[v][u]++;
        v = u;
    }
}

int main() {
    freopen("trade.in", "r", stdin);
    freopen("trade.out", "w", stdout);
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> p) {
        memset(fl, 0, sizeof fl);
        memset(c, 0, sizeof c);
        FOR(i,1,m+n+2) ke[i].clear();

        start = m + n + 1, target = m + n + 2;
        FOR(i,1,p) {
            int u, v; cin >> u >> v;
            edges[i] = make_pair(u, v);

            addEdge(u, m+v);

            if (fl[start][u] >= 2 && fl[m+v][target] >= 2) continue;

            addFlow(start, u);
            addFlow(u, m+v);
            addFlow(m+v, target);
            ++flow;
        }
        FOR(i,1,m) {
            addEdge(start, i);
            c[start][i] = 2;
            c[i][start] = -1000111;
        }
        FOR(i,m+1,m+n) {
            addEdge(i, target);
            c[i][target] = 2;
            c[target][i] = -1000111;
        }
        FOR(u,1,m) FOR(v,m+1,m+n) {
            c[u][v] = 0;
            c[v][u] = -1;
        }

        if (!check()) puts("-1");
        else {
            while (findPath()) decFlow();
            cout << flow << endl;
            FOR(i,1,p) {
                int u = edges[i].first, v = edges[i].second;
                if (fl[u][m+v]) {
                    cout << i << ' ';
                }
            }
            cout << endl;
        }
    }
    return 0;
}