
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
int n, m, good[MN], f[MN], cnt;
vector<int> ke[MN];

void dfs1(int u, int fu) {
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;
        f[v] = f[u] + 1;
        dfs1(v, u);
    }
}

int dfs2(int u, int fu) {
    int res = good[u];
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;

        if (dfs2(v, u)) {
            cnt += 2;
            res = 1;
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        memset(good, 0, sizeof good);

        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        FOR(i,1,m) {
            int u; cin >> u;
            good[u] = 1;
        }

        int root = 1;
        while (!good[root]) ++root;
        if (m == 1) {
            cout << root << endl << 0 << endl;
            continue;
        }

        memset(f, 0, sizeof f);
        dfs1(root, -1);
        int u = -1;
        FOR(i,1,n) if (good[i]) {
            if (u < 0 || f[i] > f[u]) u = i;
        }
        root = u;
        memset(f, 0, sizeof f);
        dfs1(root, -1);
        u = -1;
        FOR(i,1,n) if (good[i]) {
            if (u < 0 || f[i] > f[u]) u = i;
        }

        cnt = -f[u];
        
        if (root < u) u = root;
        cout << u << endl;

        dfs2(u, -1);
        cout << cnt << endl;
    }
}
