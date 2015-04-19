
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

const int MN = 111;
const int inf = 111 * 1011;
struct Hungary {
    int nx, ny, cost[MN][MN], fx[MN], fy[MN], matx[MN], which[MN], dist[MN];
    bool used[MN];

    void init(int _nx, int _ny) {
        nx = _nx; ny = _ny;
        memset(fx, 0, sizeof fx);
        memset(fy, 0, sizeof fy);
        memset(used, false, sizeof used);
        memset(matx, 0, sizeof matx);
        for(int i=0; i<=nx; ++i) for(int j=0; j<=ny; ++j) cost[i][j] = inf;
    }

    void add(int x, int y, int c) { cost[x][y] = min(cost[x][y],c); }

    int mincost() {
        for(int x=1; x<=nx; ++x) {
            int y0 = 0; matx[0] = x;
            for(int y=0; y<=ny; ++y) { dist[y] = inf + 1; used[y] = false; }

            do {
                used[y0] = true;
                int x0 = matx[y0], delta = inf + 1, y1;

                for(int y=1; y<=ny; ++y) if (!used[y]) {
                    int curdist = cost[x0][y] - fx[x0] - fy[y];
                    if (curdist < dist[y]) {
                        dist[y] = curdist;
                        which[y] = y0;
                    }
                    if (dist[y] < delta) {
                        delta = dist[y];
                        y1 = y;
                    }
                }

                for(int y=0; y<=ny; ++y) if (used[y]) {
                    fx[matx[y]] += delta;
                    fy[y] -= delta;
                } else dist[y] -= delta;

                y0 = y1;
            } while (matx[y0] != 0);

            do {
                int y1 = which[y0];
                matx[y0] = matx[y1];
                y0 = y1;
            } while (y0);
        }
//      return -fy[0]; // nếu luôn đảm bảo có bộ ghép đầy đủ
        int ret = 0;
        for(int y=1; y<=ny; ++y) {
            int x = matx[y];
            if (cost[x][y] < inf) ret += cost[x][y];
        }
        return ret;
    }
} hungary;


int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n; cin >> n;
        hungary.init(n, n);
        FOR(i,1,n) FOR(j,i+1,n) {
            int c; cin >> c;
            hungary.add(i, j, c);
            hungary.add(j, i, c);
        }
        cout << "Case " << test << ": " << hungary.mincost() << '\n';
    }
    return 0;
}
