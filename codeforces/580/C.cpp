
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;

int n, cat[MN], m, res;
vector<int> ke[MN];

void dfs(int u, int fu, int cur) {
    if (cat[u]) ++cur;
    else cur = 0;
    if (cur > m) return ;

    bool leaf = true;
    for(int v : ke[u]) {
        if (v == fu) continue;

        leaf = false;

        dfs(v, u, cur);
    }

    if (leaf) ++res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) cin >> cat[i];
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        res = 0;
        dfs(1, -1, 0);
        cout << res << endl;
    }
}
