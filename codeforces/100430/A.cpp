
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 200111;

int n, color[MN], a[MN];

vector < vector<int> > g, gt;
vector<int> pos[MN];
vector<bool> used;
vector<int> order, comp;

void init() {
    g.clear(); gt.clear();
    used.clear();
    order.clear();
    comp.clear();

    g.resize(n*4);
    gt.resize(n*4);

    FOR(i,0,n) pos[i].clear();
}

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

int res[MN];

int main() {
    ios :: sync_with_stdio(false);
    freopen("chip.in", "r", stdin);
    freopen("chip.out", "w", stdout);

    while (cin >> n) {
        init();

        REP(i,n) cin >> color[i];
        REP(i,n+n) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }


        FOR(i,1,n) {
            int x = pos[i][0], y = pos[i][1];
            // vx | vy
            int vx = 2*x, vy = 2*y;
            addEdge(vx^1, vy);
            addEdge(vy^1, vx);

            // !vx | !vy
            addEdge(vx, vy^1);
            addEdge(vy, vx^1);
        }
        
        REP(i,n+n) {
            int u = a[i]-1, v = a[(i+1) % (n+n)]-1;
            if (color[u] == color[v]) {
                int vx = i*2;
                int vy = ((i+1) % (n+n)) * 2;
                addEdge(vx, vy^1);
                addEdge(vy, vx^1);
            }
        }

        n = 4*n;
        used.assign(n, false);
        REP(i,n)
            if (!used[i]) {
                dfs1(i);
            }
        comp.assign (n, -1);
        for (int i=0, j=0; i<n; ++i) {
            int v = order[n-i-1];
            if (comp[v] == -1) dfs2 (v, j++);
        }
        bool ok = true;
        REP(i,n)
            if (comp[i] == comp[i^1]) {
                cout << "NO" << endl;
                ok = false;
                break;
            }
        if (!ok) continue;

        cout << "YES" << endl;
        for (int i=0; i<n; i += 2) {
            int ans = comp[i] > comp[i^1] ? i : i^1; 
            if (ans == i) res[a[i/2]] = i/2 + 1;
        }
        FOR(i,1,n/4) cout << res[i] << ' '; cout << endl;
    }
}
