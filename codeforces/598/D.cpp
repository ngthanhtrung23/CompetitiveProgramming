
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 1011;

char a[MN][MN];
int m, n, q;
int visited[MN][MN], cur, res[MN * MN];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

int bfs(int u, int v) {
    queue<int> qu, qv;
    qu.push(u);
    qv.push(v);

    int res = 0;
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 1 || uu > m || vv < 1 || vv > n) continue;

            if (a[uu][vv] == '*') {
                ++res;
                continue;
            }
            if (visited[uu][vv]) continue;

            visited[uu][vv] = visited[u][v];
            qu.push(uu);
            qv.push(vv);
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d%d\n", &m, &n, &q) == 3) {
        memset(visited, 0, sizeof visited);
        cur = 0;
        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        FOR(i,1,m) FOR(j,1,n) if (!visited[i][j] && a[i][j] == '.') {
            ++cur;
            visited[i][j] = cur;
            res[cur] = bfs(i, j);
        }
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            printf("%d\n", res[visited[u][v]]);
        }
    }
}
