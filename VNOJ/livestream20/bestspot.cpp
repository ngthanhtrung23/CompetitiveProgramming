#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 511;
int c[MN][MN];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int nVertex, nGood, nEdges;
    cin >> nVertex >> nGood >> nEdges;
    vector<int> good(nGood);
    for (int& x : good) cin >> x;

    // init
    memset(c, 0x3f, sizeof c);
    for (int i = 1; i <= nVertex; i++) {
        c[i][i] = 0;
    }

    // read edges
    while (nEdges--) {
        int u, v, cost; cin >> u >> v >> cost;
        c[u][v] = min(c[u][v], cost);
        c[v][u] = c[u][v];
    }

    // floyd
    FOR(k,1,nVertex) {
        FOR(i,1,nVertex) {
            FOR(j,1,nVertex) {
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
            }
        }
    }

    // find best
    pair<int,int> res = {1e15, 0};
    for (int i = 1; i <= nVertex; i++) {
        int sum = 0;
        for (int x : good) {
            sum += c[i][x];
        }

        res = min(res, {sum, i});
    }
    cout << res.second << endl;
    return 0;
}
