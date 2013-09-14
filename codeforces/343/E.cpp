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

int ok[1011], saveCap[1011][1011], qu[1011], cap[1011][1011];
int answer[1011][1011], parent[1011], n;
void bfs(int start) {
    memset(ok,0,sizeof ok);
    int first=1, last=1; qu[1]=start;
    while (first <= last) {
        int u=qu[first++];
        REP(v,n) {
            if (cap[u][v] && !ok[v]) {
                ok[v]=1;
                qu[++last]=v;
            }
        }
    }
}

int first, last, tr[1011];

bool findPath(int n, int start, int target) {
    memset(tr, -1, sizeof tr);
    tr[start] = start; qu[first = last = 1] = start;

    while (first <= last) {
        int u = qu[first++];
        REP(v,n) if (tr[v] < 0 && cap[u][v] > 0) {
            tr[v] = u;
            qu[++last] = v;
            if (v == target) return true;
        }
    }
    return false;
}

int incFlow(int start, int target) {
    int v = target, delta = 1000111000;
    while (v != start) {
        int u = tr[v];
        delta = min(delta, cap[u][v]);
        v = u;
    }
    v = target;
    while (v != start) {
        int u = tr[v];
        cap[u][v] -= delta;
        cap[v][u] += delta;
        v = u;
    }
    return delta;
}

int maxFlow(int n, int u, int v) {
    int res = 0;
    while (findPath(n, u, v)) {
        res += incFlow(u, v);
    }
    return res;
}

vector< pair<int,int> > ke[1011];
set< pair<int,int> > block;

vector<int> go(int start) {
    int ln = 1000111, saveu = -1, savev = -1;
    memset(tr, -1, sizeof tr);

    qu[first = last = 1] = start; tr[start] = start;
    while (first <= last) {
        int u = qu[first++];
        REP(i,ke[u].size()) {
            int v = ke[u][i].first, c = ke[u][i].second;

            if (tr[v] >= 0) continue;
            if (block.find(make_pair(u, v)) != block.end()) continue;

            tr[v] = u;
            qu[++last] = v;
            if (c < ln) {
                ln = c;
                saveu = u;
                savev = v;
            }
        }
    }

    if (last == 1) {
        vector<int> res; res.clear();
        res.push_back(start);
        return res;
    }

    block.insert(make_pair(saveu, savev));
    block.insert(make_pair(savev, saveu));

    vector<int> l = go(saveu);
    vector<int> r = go(savev);

    vector<int> res; res.clear();
    for(int i = l.size()-1; i >= 0; --i)
        res.push_back(l[i]);
    REP(i,r.size())
        res.push_back(r[i]);
    return res;
}

void solve() {
    REP(i,n) parent[i]=0;
    REP(i,n) REP(j,n) answer[i][j]=2000111011;
    REP(i,n) REP(j,n) saveCap[i][j] = cap[i][j];
    
    int res = 0;
    FOR(i,1,n-1) {
        REP(u,n) REP(v,n) cap[u][v] = saveCap[u][v];
        int f=maxFlow(n, i, parent[i]);
        bfs(i);
        FOR(j,i+1,n-1)
            if (ok[j] && parent[j]==parent[i])
                parent[j]=i;
        
        answer[i][parent[i]] = answer[parent[i]][i] = f;
        res += f;

        ke[i].push_back(make_pair(parent[i], f));
        ke[parent[i]].push_back(make_pair(i, f));
    }
    cout << res << endl;
    vector<int> path = go(0);
    REP(i,path.size()) cout << path[i]+1 << ' ';
    cout << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    int m;
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v; cin >> u >> v;
        --u; --v;
        cin >> cap[u][v];
        cap[v][u] = cap[u][v];
    }
    solve();
    return 0;
}
