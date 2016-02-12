
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

const int MN = 500111;
int n, h[MN];
vector<int> ke[MN], cur;

void dfs(int u, int fu) {
    if (SZ(ke[u]) == 1) {
        cur.push_back(h[u]);
    }
    for(int v : ke[u]) {
        if (v == fu) continue;
        h[v] = h[u] + 1;
        dfs(v, u);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        int res = 0;
        for(int u : ke[1]) {
            h[u] = 1;
            cur.clear();
            dfs(u, 1);

            sort(cur.begin(), cur.end());
            reverse(cur.begin(), cur.end());
            REP(i,SZ(cur)) res = max(res, i + cur[i]);
        }
        cout << res << endl;
    }
}
