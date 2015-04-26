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

const int MN = 200111;

vector<int> ke[MN];
int n, m;
int f[2][MN];

void dfs1(int u) {
    if (ke[u].empty()) {
        f[0][u] = f[1][u] = 1;
        ++m;
        return ;
    }
    f[0][u] = 0;
    f[1][u] = 1000111000;

    for(int v : ke[u]) {
        dfs1(v);

        f[0][u] += f[1][v];
        f[1][u] = min(f[1][u], f[0][v]);
    }
}

void dfs2(int u) {
    if (ke[u].empty()) {
        f[0][u] = f[1][u] = 1;
        return ;
    }

    f[0][u] = 1000111000;
    f[1][u] = 0;

    for(int v : ke[u]) {
        dfs2(v);

        f[0][u] = min(f[0][u], f[1][v]);
        f[1][u] += f[0][v];
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();

        m = 0;
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
        }
        dfs1(1);
        printf("%d ", m+1-f[1][1]);

        dfs2(1);
        printf("%d\n", f[1][1]);
    }
    return 0;
}
