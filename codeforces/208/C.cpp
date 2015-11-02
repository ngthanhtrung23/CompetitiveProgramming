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

int n;
const int MN = 111;
vector<int> ke[MN];
int c[2][MN];
long double f[2][MN];

void bfs(int turn, int start) {
    memset(c[turn], -1, sizeof c[turn]);
    memset(f[turn], 0, sizeof f[turn]);

    c[turn][start] = 0;
    f[turn][start] = 1.0;
    queue<int> qu; qu.push(start);
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        REP(i,SZ(ke[u])) {
            int v = ke[u][i];
            if (c[turn][v] < 0) {
                c[turn][v] = c[turn][u] + 1;
                f[turn][v] = f[turn][u];
                qu.push(v);
            }
            else if (c[turn][v] == c[turn][u] + 1) {
                f[turn][v] += f[turn][u];
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int m;
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        bfs(0, 1);
        bfs(1, n);
        long double res = 1.0;
        FOR(i,2,n-1) {
            if (c[0][i] + c[1][i] == c[0][n]) {
                res = max(res, 2.0 * f[0][i] * f[1][i] / f[0][n]);
            }
        }
        cout << (fixed) << setprecision(9) << res << endl;
    }
}
