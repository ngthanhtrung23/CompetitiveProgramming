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
int n;
ll x, y;
vector<int> ke[MN];
int bad[MN], res;

bool isStar() {
    FOR(i,1,n) if (SZ(ke[i]) == n-1) return true;
    return false;
}

void dfs(int u, int fu) {
    int cnt = 0;
    for(int v : ke[u]) if (v != fu) {
        dfs(v, u);
        if (bad[v] == 0) ++cnt;
    }

    if (cnt == 0) bad[u] = 0;
    else if (cnt == 1) bad[u] = 0, ++res;
    else {
        bad[u] = 1;
        res += 2;
    }
}

ll solve() {
    if (x >= y) {
        if (isStar()) return x + (n - 2) * y;
        else return (n - 1LL) * y;
    }

    memset(bad, 0, sizeof bad);
    res = 0;
    dfs(1, -1);
    return res * x + (n - 1 - res) * y;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> x >> y) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        cout << solve() << endl;
    }
}
