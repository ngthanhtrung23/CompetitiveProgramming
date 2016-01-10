
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

const int MN = 200111;
ll f[MN];
vector<int> ke[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        ll res = 0;
        FOR(u,1,n) {
            f[u] = 1;
            for(int v : ke[u]) {
                if (v < u) f[u] = max(f[u], f[v] + 1);
            }
            res = max(res, f[u] * SZ(ke[u]));
        }
        cout << res << endl;
    }
}
