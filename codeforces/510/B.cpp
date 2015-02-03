#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int m, n;
char a[55][55];
bool visited[55][55];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

bool dfs(int u, int v, int fu, int fv) {
    visited[u][v] = true;
    REP(dir,4) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (uu < 1 || uu > m || vv < 1 || vv > n || a[uu][vv] != a[u][v]) continue;
        if (uu == fu && vv == fv) continue;
        
        if (visited[uu][vv]) return true;

        if (dfs(uu, vv, u, v)) return true;
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        memset(visited, false, sizeof visited);

        bool res = false;
        FOR(i,1,m) FOR(j,1,n)
            if (!visited[i][j]) {
                if (res) break;
                bool ok = dfs(i, j, -1, -1);
                if (ok) {
                    res = true;
                    break;
                }
            }
        if (res) cout << "Yes"; else cout << "No";
        cout << endl;
    }
    return 0;
}
