#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int getCode(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a' + 1;
    return c - 'A' + 27;
}

char getChar(int c) {
    if (c <= 26) return 'a' + c - 1;
    return 'A' + c - 27;
}

const int MN = 511;
const int inf = 1000111000;

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

int c[111][111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n, k;
    while (cin >> n >> k) {
        string a, b;
        cin >> a >> b;
        swap(a, b);

        memset(c, 0, sizeof c);
        REP(i,n) c[getCode(a[i])][getCode(b[i])] += 1;

        int VAL = 2000111;
        hungary.init(k, k);
        FOR(i,1,k) FOR(j,1,k) hungary.add(i, j, VAL - c[i][j]);

        int res = hungary.mincost();
        res = VAL * k - res;

        cout << res << endl;
        FOR(i,1,k) {
            int j = hungary.matx[i];
            cout << getChar(j);
        }
        cout << endl;
    }
    return 0;
}
