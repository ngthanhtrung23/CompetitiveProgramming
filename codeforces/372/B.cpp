
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

int m, n, q;
char a[44][44];
int f[44][44][44][44], sum[44][44], startsFrom[44][44][44][44];

int getSum(int x, int y, int i, int j) {
    return sum[i][j] - sum[x-1][j] - sum[i][y-1] + sum[x-1][y-1];
}

void init() {
    FOR(i,1,m) FOR(j,1,n) sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i][j] - '0';

    FORD(x,m,1) FORD(y,n,1) {
        FOR(i,x,m) FOR(j,y,n) {
            startsFrom[x][y][i][j] =
                + startsFrom[x][y][i-1][j]
                + startsFrom[x][y][i][j-1]
                - startsFrom[x][y][i-1][j-1]
                + ((getSum(x, y, i, j) == 0) ? 1 : 0);

            f[x][y][i][j] = startsFrom[x][y][i][j]
                + f[x+1][y][i][j] + f[x][y+1][i][j] - f[x+1][y+1][i][j];
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> q) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        init();
        while (q--) {
            int u, v, x, y; cin >> u >> v >> x >> y;
            cout << f[u][v][x][y] << '\n';
        }
    }
    return 0;
}

