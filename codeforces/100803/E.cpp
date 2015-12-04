#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};
const int rev_dir[4] = {1,0,3,2};

#define y0 y0___
int nRoad, x0, y0, nTime;
bool dir[55][55][4];
int fixedPos[1011];
int dirId[333];
bool visited[1011][55][55][4];
bool res[55][55];

struct Road {
    int x1, y1, x2, y2;
    void read() {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        if (x1 == x2) {
            FOR(y,y1,y2-1) dir[x1][y][3] = true;
            FOR(y,y1+1,y2) dir[x1][y][2] = true;
        }
        if (y1 == y2) {
            FOR(x,x1,x2-1) dir[x][y1][1] = true;
            FOR(x,x1+1,x2) dir[x][y1][0] = true;
        }
    }
} roads[55];

void init() {
    memset(dir, 0, sizeof dir);
    memset(fixedPos, -1, sizeof fixedPos);
    memset(visited, 0, sizeof visited);
    memset(res, 0, sizeof res);
}

int main() {
    dirId['N'] = 3;
    dirId['S'] = 2;
    dirId['W'] = 0;
    dirId['E'] = 1;
    while (scanf("%d%d%d%d", &nRoad, &x0, &y0, &nTime) == 4) {
        init();
        FOR(i,1,nRoad) {
            roads[i].read();
        }
        int sumDist = 0;
        FOR(i,1,nTime) {
            int dir; char c;
            int dist; scanf("%d %c", &dist, &c);
            sumDist += dist;
            fixedPos[sumDist] = dirId[c];
        }

        queue<int> qt;
        queue<int> qu;
        queue<int> qv;
        queue<int> qd;
        REP(d,4) if (dir[x0][y0][d]) {
            qt.push(0);
            qu.push(x0);
            qv.push(y0);
            qd.push(d);
            visited[0][x0][y0][d] = true;
        }
        while (!qt.empty()) {
            int t = qt.front(); qt.pop();
            int u = qu.front(); qu.pop();
            int v = qv.front(); qv.pop();
            int d = qd.front(); qd.pop();
            if (t == sumDist) {
                res[u][v] = true;
                continue;
            }

            int uu = u + di[d];
            int vv = v + dj[d];
            int tt = t + 1;
            REP(dd,4) if (dir[uu][vv][dd] && dd != rev_dir[d]) {
                if (fixedPos[tt] >= 0 && fixedPos[tt] != dd
                        && fixedPos[tt] != d) continue;
                if (visited[tt][uu][vv][dd]) continue;

                visited[tt][uu][vv][dd] = true;
                qt.push(tt);
                qu.push(uu);
                qv.push(vv);
                qd.push(dd);
            }
        }
        FOR(i,0,50) FOR(j,0,50) if (res[i][j]) {
            printf("%d %d\n", i, j);
        }
        puts("");
    }
}
