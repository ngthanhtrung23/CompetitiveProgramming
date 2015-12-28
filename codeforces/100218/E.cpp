
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

const int MN = 111;

int nColor;
int n[2];
int ke[2][MN][MN];
vector<int> ke_rev[2][MN][MN];
int visited[MN][MN];

void dfs(int u, int v) {
    visited[u][v] = 1;
    FOR(c,1,nColor) {
        for(int uu : ke_rev[0][u][c]) {
            for(int vv : ke_rev[1][v][c]) {
                if (uu && vv && !visited[uu][vv]) {
                    dfs(uu, vv);
                }
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("mazes.in", "r", stdin);
    freopen("mazes.out", "w", stdout);
    while (cin >> nColor) {
        memset(ke, 0, sizeof ke);
        REP(t,2) {
            int m; cin >> n[t] >> m;
            FOR(i,1,n[t]) FOR(c,1,nColor) ke_rev[t][i][c].clear();

            while (m--) {
                int u, v, c; cin >> u >> v >> c;

                ke[t][u][c] = v;
                ke_rev[t][v][c].push_back(u);
            }
        }
        memset(visited, 0, sizeof visited);
        dfs(n[0], n[1]);

        if (!visited[1][1]) cout << "no common solution" << endl;
        else {
            try {
                int u = 1, v = 1;
                visited[1][1] = 2;
                vector<int> res;
                while (u != n[0] || v != n[1]) {
                    FOR(c,1,nColor) {
                        int uu = ke[0][u][c], vv = ke[1][v][c];
                        if (uu && vv && visited[uu][vv]) {
                            if (visited[uu][vv] == 2) throw 1;

                            visited[uu][vv] = 2;
                            u = uu; v = vv;
                            res.push_back(c);
                            break;
                        }
                    }
                }
                cout << SZ(res) << '\n';
                for(int x : res) cout << x << ' '; cout << '\n';
            } catch (int e) {
                cout << "no smallest solution" << endl;
            }
        }
    }
}
