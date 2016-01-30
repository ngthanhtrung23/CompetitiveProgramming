
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 411;

int nVar, need[MN], nPhrase, a[MN][MN], id[MN];

int n;
vector < vector<int> > g, gt;
vector<bool> used;
vector<int> order, comp;
void dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs1 (to);
	}
	order.push_back (v);
}
void dfs2 (int v, int cl) {
    comp[v] = cl;
    for (size_t i=0; i<gt[v].size(); ++i) {
        int to = gt[v][i];
        if (comp[to] == -1)
            dfs2 (to, cl);
	}
}

void addEdge(int u, int v) {
    g[u].push_back(v);
    gt[v].push_back(u);
}

void solve() {
    n = nVar * 2;
    g.resize(n + 5);
    gt.resize(n + 5);
    REP(i,n) {
        g[i].clear();
        gt[i].clear();
    }
    REP(i,nVar) {
        if (id[i*2] < 0 && id[i*2+1] < 0) {
            // can not put any phrase
            cout << "NO" << endl;
            return ;
        }

        if (id[i*2+1] < 0) {
            addEdge(i*2+1, i*2);
        }
    }
//    PR0(id, n);

    REP(i,n) FOR(j,i+1,n-1) if ((i ^ j) != 1) {
        int u = id[i];
        int v = id[j];
        REP(x,nVar) if (a[u][x] == a[v][x]) {
            addEdge(i, j^1);
            addEdge(j, i^1);
        }
    }

    used.assign (n, false);
    REP(i,n)
        if (!used[i])    dfs1 (i);
    comp.assign (n, -1);
    for (int i=0, j=0; i<n; ++i) {
        int v = order[n-i-1];
        if (comp[v] == -1) dfs2 (v, j++);
    }
    REP(i,n)
        if (comp[i] == comp[i^1]) {
            cout << "NO" << endl;
            return ;
        }
    cout << "YES" << endl;
    for (int i=0; i<n; i += 2) {
        int ans = comp[i] > comp[i^1] ? i : i^1; 
        cout << 1 + id[ans] << ' ';
    }
    cout << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("show.in", "r", stdin);
    freopen("show.out", "w", stdout);
    while (cin >> nVar) {
        REP(i,nVar) cin >> need[i];
        cin >> nPhrase;
        REP(i,nPhrase) REP(j,nVar) cin >> a[i][j];

        memset(id, -1, sizeof id);
        REP(i,nVar) {
            int x = 2*i;
            REP(j,nPhrase) {
                if (a[j][i] == need[i]) id[x++] = j;
            }
        }
        solve();
    }
}
