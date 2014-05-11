#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

int n;
vector<int> ke[MN];
int a[MN], b[MN];
vector<int> res;

void visit(int u, int f0, int f1, int father) {
    a[u] ^= f0;
    if (a[u] == b[u]) {
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (v == father) continue;
            visit(v, f1, f0, u);
        }
    }
    else {
        res.push_back(u);
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (v == father) continue;
            visit(v, f1, f0 ^ 1, u);
        }
    }
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
        FOR(i,1,n) cin >> b[i];

        res.clear();
        visit(1, 0, 0, -1);
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i] << endl;
    }
    return 0;
}
