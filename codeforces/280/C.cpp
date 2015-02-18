
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

const int MN = 100111;
int n;
vector<int> ke[MN];
double res = 0.0;
int h[MN];

void dfs(int u, int fu) {
    res += 1.0 / h[u];
    for(int v : ke[u]) {
        if (v == fu) continue;

        h[v] = h[u] + 1;
        dfs(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(14);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        h[1] = 1;
        res = 0.0;
        dfs(1, -1);
        cout << res << endl;
    }
    return 0;
}
