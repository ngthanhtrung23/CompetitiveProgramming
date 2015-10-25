
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
const int MN2 = MN * MN;

int m, n;
char a[MN][MN];
int d[4][MN][MN];

int go[4][4];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

void bfs(int turn) {
    queue<int> qu, qv;

    memset(d[turn], -1, sizeof d[turn]);
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == turn + '0') {
        qu.push(i);
        qv.push(j);
        d[turn][i][j] = 0;
    }

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 1 || uu > m || vv < 1 || vv > n) continue;
            if (a[uu][vv] == '#') continue;
            if (d[turn][uu][vv] >= 0) continue;

            d[turn][uu][vv] = d[turn][u][v] + 1;
            qu.push(uu);
            qv.push(vv);
        }
    }

    FOR(i,1,m) FOR(j,1,n) if (a[i][j] >= '0' && a[i][j] <= '3' && d[turn][i][j] != -1) {
        int to = a[i][j] - '0';
        go[turn][to] = min(go[turn][to], d[turn][i][j] - 1);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        int res = MN2;

        FOR(i,1,3) FOR(j,1,3) go[i][j] = MN2;
        FOR(i,1,3) go[i][i] = 0;
        FOR(turn,1,3) bfs(turn);

        int x[4];
        FOR(i,1,3) x[i] = i;
        do {
            res = min(res, go[x[1]][x[2]] + go[x[2]][x[3]]);
        } while (next_permutation(x+1, x+4));

        FOR(i,1,m) FOR(j,1,n)
            if (d[1][i][j] >= 0
                    && d[2][i][j] >= 0
                    && d[3][i][j] >= 0) {
                res = min(res, d[1][i][j] + d[2][i][j] + d[3][i][j] - 2);
            }

        if (res == MN2) cout << -1 << endl;
        else cout << res << endl;
    }
}
