#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;

int f[MN][2], a[MN], n;
vector<int> ke[MN];

void dfs(int u) {
    int g[2];
    g[0] = 0;
    g[1] = -1000111000111LL;

    for(int v : ke[u]) {
        dfs(v);

        int g0 = max(g[0] + f[v][0], g[1] + f[v][1]);
        int g1 = max(g[0] + f[v][1], g[1] + f[v][0]);
        g[0] = g0;
        g[1] = g1;
    }

    f[u][0] = max({
            0LL,  // choose nobody
            g[0]  // do not choose u, choose even from subordinates
            });
    f[u][1] = max({
            g[1],  // choose odd from subordinates
            a[u],  // choose only u
            a[u] + g[0]
            });
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) {
            int pi; cin >> pi >> a[i];
            if (i > 1) ke[pi].push_back(i);
        }
        dfs(1);
        cout << max(f[1][0], f[1][1]) << endl;
    }
}
