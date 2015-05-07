
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

const int MN = 3011;
const int oo = 1000111;

int n;
vector<int> ke[MN];
int d[MN][MN];

void bfs(int root) {
    queue<int> qu;
    qu.push(root);
    d[root][root] = 0;

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for(int v : ke[u]) {
            if (d[root][v] == oo) {
                d[root][v] = d[root][u] + 1;
                qu.push(v);
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int m;
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();

        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        FOR(i,1,n) FOR(j,1,n) d[i][j] = oo;

        FOR(i,1,n) {
            d[i][i] = 0;
            bfs(i);
        }

        int s1, t1, l1, s2, t2, l2;
        scanf("%d%d%d%d%d%d", &s1, &t1, &l1, &s2, &t2, &l2);
        if (d[s1][t1] > l1 || d[s2][t2] > l2) {
            cout << -1 << endl;
            continue;
        }
        if (s1 == t1) {
            cout << m - d[s2][t2] << endl;
            continue;
        }
        if (s2 == t2) {
            cout << m - d[s1][t1] << endl;
            continue;
        }

        int res = d[s1][t1] + d[s2][t2];
        FOR(u,1,n) FOR(v,1,n)
            if (d[s1][u] + d[u][v] + d[v][t1] <= l1
                    && d[s2][u] + d[u][v] + d[v][t2] <= l2)
                res = min(res, d[s1][u] + d[s2][u] + d[u][v] + d[v][t1] + d[v][t2]);

        swap(s2, t2);
        FOR(u,1,n) FOR(v,1,n)
            if (d[s1][u] + d[u][v] + d[v][t1] <= l1
                    && d[s2][u] + d[u][v] + d[v][t2] <= l2)
                res = min(res, d[s1][u] + d[s2][u] + d[u][v] + d[v][t1] + d[v][t2]);

        cout << m - res << endl;
    }
    return 0;
}
