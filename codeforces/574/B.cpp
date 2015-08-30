
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
using namespace std;

int eu[4011], ev[4011], deg[4011];
bool ke[4011][4011];

int main() {
    ios :: sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        memset(deg, 0, sizeof deg);
        memset(ke, 0, sizeof ke);
        FOR(i,1,m) {
            cin >> eu[i] >> ev[i];
            ++deg[eu[i]];
            ++deg[ev[i]];

            ke[eu[i]][ev[i]] = ke[ev[i]][eu[i]] = true;
        }

        int res = 1e9;
        FOR(i,1,m) {
            int u = eu[i];
            int v = ev[i];
            FOR(w,1,n) if (w != u && w != v && ke[u][w] && ke[v][w]) {
                res = min(res, deg[u] + deg[v] + deg[w] - 6);
            }
        }
        if (res == 1e9) res = -1;
        cout << res << endl;
    }
}
