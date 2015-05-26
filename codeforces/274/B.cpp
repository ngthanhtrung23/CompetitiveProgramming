
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

#define dec dec__
long long a[MN], inc[MN], dec[MN];
vector<int> ke[MN];
int n;

void dfs(int u, int fu = -1) {
    inc[u] = dec[u] = 0;
    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs(v, u);

        inc[u] = max(inc[u], inc[v]);
        dec[u] = max(dec[u], dec[v]);
    }

    a[u] = a[u] + inc[u] - dec[u];
    if (a[u] > 0) dec[u] += a[u];
    else if (a[u] < 0) inc[u] -= a[u];
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        FOR(i,1,n) cin >> a[i];

        dfs(1);
        cout << inc[1] + dec[1] << endl;
    }
    return 0;
}
