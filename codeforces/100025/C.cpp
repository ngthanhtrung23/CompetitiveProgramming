#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);
const int MN = 300111;

int f[2][MN], g[MN], save[MN];
vector<int> ke[MN];

void visit(int u, int fu) {
    f[0][u] = f[1][u] = 0;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        visit(v, u);
        int cur = f[0][v] + 1;
        if (cur > f[0][u]) {
            f[1][u] = f[0][u];
            save[u] = v;
            f[0][u] = cur;
        }
        else f[1][u] = max(f[1][u], cur);
    }
}

void visit2(int u, int fu) {
    if (fu == -1) g[u] = 0;
    else {
        if (save[fu] == u) g[u] = max(g[fu] + 1, f[1][fu] + 1);
        else g[u] = max(g[fu] + 1, f[0][fu] + 1);
    }
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        visit2(v, u);
    }
}

int cur[MN], top, res[MN];

void visit3(int u, int fu) {
    top = 0;
    if (fu >= 0) cur[++top] = g[u];
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        cur[++top] = f[0][v] + 1;
    }
    sort(cur + 1, cur + top + 1);
//    cout << u << ": "; FOR(i,1,top) cout << cur[i] << ' '; puts("");
    
    FOR(i,1,top) {
        res[cur[i]] = max(res[cur[i]], top - i + 1);
    }
    
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        visit3(v, u);
    }
}

int main() {
    freopen("amoeba.in", "r", stdin);
    freopen("amoeba.out", "w", stdout);
    int n, a, b, u, v; scanf("%d%d%d", &n, &a, &b);
    FOR(i,2,n) {
        scanf("%d%d", &u, &v);
        ke[u].PB(v);
        ke[v].PB(u);
    }
    visit(1, -1);
    visit2(1, -1);
//    FOR(i,1,n) cout << f[0][i] << ' '; puts("");
//    FOR(i,1,n) cout << f[1][i] << ' '; puts("");
//    FOR(i,1,n) cout << g[i] << ' '; puts("");
    visit3(1, -1);
    FORD(i,n,1) res[i] = max(res[i+1], res[i]);
    FOR(i,a,b) printf("%d\n", res[i]);
    return 0;
}
