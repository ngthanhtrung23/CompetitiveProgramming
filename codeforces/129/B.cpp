
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

const int MN = 111;
vector<int> ke[MN];
int deg[MN], n;

int main() {
    ios :: sync_with_stdio(false);
    int m;
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        memset(deg, 0, sizeof deg);
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }
        int res = 0;
        while (true) {
            vector<int> cur;
            FOR(i,1,n) if (deg[i] == 1) cur.push_back(i);
            if (cur.empty()) break;

            ++res;
            for(int u : cur)
                for(int v : ke[u]) {
                    --deg[v];
                    --deg[u];
                }
        }
        cout << res << endl;
    }
    return 0;
}

