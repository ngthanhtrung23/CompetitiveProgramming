#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 211;
const int MN2 = MN * MN;

int m, n, q;
char a[MN][MN];
int id[MN][MN];
int di[11], dj[11];
int V;
vector<int> G[MN2];

bool outside(int u, int v) {
    return u < 1 || u > m || v < 1 || v > n;
}

pair<int,int> go(int u, int v) {
    int dir = a[u][v] - '0';
    int uu = u + di[dir], vv = v + dj[dir];
    if (outside(uu, vv)) uu = u, vv = v;

    return make_pair(uu, vv);
}

struct DirectedDfs {
    vector<int> num, low, current, S;
    int counter;
    vector< vector<int> > scc;

    DirectedDfs() : num(V, -1), low(V, 0), current(V, 0), counter(0) {
        REP(i,V) if (num[i] == -1) dfs(i);
    }

    void dfs(int u) {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        REP(j, G[u].size()) {
            int v = G[u][j];
            if (num[v] == -1) dfs(v);
            if (current[v] && low[v] < low[u]) low[u] = low[v];
        }
        if (low[u] == num[u]) {
            scc.push_back(vector<int>());
            while (1) {
                int v = S.back(); S.pop_back(); current[v] = 0;
                scc.back().push_back(v);
                if (u == v) break;
            }
        }
    }
};

vector<int> ke[MN2];
int vao[MN2], sccId[MN2], mask[MN2];
char s[1000111];

#define next next__
int next[10][1000111];
int len;

bool dfs(int u, int start) {
    if (start >= len) return true;
    int to = len;
    // find first character that can not be covered by this vertex
    REP(cur,10)
        if (!((mask[u] >> cur) & 1)) {
            if (to > next[cur][start])
                to = next[cur][start];
        }
    if (to == len) return true;

    for(int v : ke[u]) {
        if (dfs(v, to)) return true;
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%d%d%d\n", &m, &n, &q) == 3) {
        // read input
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        REP(i,10) scanf("%d%d\n", &di[i], &dj[i]);
        // init id & G
        V = 0;
        FOR(i,1,m) FOR(j,1,n) {
            id[i][j] = V++;
        }
        REP(i,V) G[i].clear();
        FOR(i,1,m) FOR(j,1,n) {
            auto p = go(i, j);
            int u = id[i][j];
            int v = id[p.first][p.second];

            G[v].push_back(u);
        }
//        FOR(i,1,m) {
//            PR(id[i], n);
//        }
        // compress the graph
        DirectedDfs tree;
        int k = SZ(tree.scc);
//        DEBUG(k);
        REP(i,k) {
//            PR0(tree.scc[i], SZ(tree.scc[i]));
            vao[i] = 0;
            ke[i].clear();
            for(int x : tree.scc[i]) sccId[x] = i;
            mask[i] = 0;
        }
        FOR(i,1,m) FOR(j,1,n) {
            int u = sccId[ id[i][j] ];
            mask[u] |= 1<<(a[i][j] - '0');
        }
//        PR0(mask, k);
        REP(u,V) {
            for(int v : G[u]) {
                int uu = sccId[u];
                int vv = sccId[v];

                if (uu == vv) continue;

                ke[uu].push_back(vv);
                vao[vv] += 1;
            }
        }
        // answer queries
        while (q--) {
            scanf("%s\n", &s[0]);
            len = strlen(s);
            reverse(s, s+len);
            REP(cur,10) {
                next[cur][len] = len;
                FORD(i,len-1,0) {
                    if (s[i] - '0' == cur) next[cur][i] = i;
                    else next[cur][i] = next[cur][i+1];
                }
            }

            bool ok = false;
            REP(i,k) if (!vao[i] && dfs(i, 0)) {
                ok = true;
                puts("YES");
                break;
            }
            if (!ok) puts("NO");
        }
    }
}
