
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

const int MN = 100111;
vector<int> ke[MN];
int n, f[3][MN];

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}

void dfs(int u, int fu) {
    f[0][u] = 0;

    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs(v, u);

        f[0][u] += max3(f[0][v], f[1][v], f[2][v]);
    }

    f[1][u] = -MN;
    f[2][u] = -MN;

    int best1 = -MN, best2 = -MN * 2;

    for(int v : ke[u]) {
        if (v == fu) continue;

        int cur = max(f[0][v], f[1][v])
            - max3(f[0][v], f[1][v], f[2][v]);

        if (cur > best1) {
            best2 = best1;
            best1 = cur;
        }
        else if (cur > best2) best2 = cur;
    }
    f[1][u] = f[0][u] + best1 + 1;
    f[2][u] = f[0][u] + best1 + best2 + 2;

    if (f[1][u] < 0) f[1][u] = -MN;
    if (f[2][u] < 0) f[2][u] = -MN;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("tour.in", "r", stdin);
    freopen("tour.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        dfs(1, -1);

        int res = max3(f[0][1], f[1][1], f[2][1]);
        cout << n - res << endl;
    }
}
