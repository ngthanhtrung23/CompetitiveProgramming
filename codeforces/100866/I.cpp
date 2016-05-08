
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 511;
bool visited[MN][MN], ver[MN][MN], hor[MN][MN];

void init() {
    memset(visited, 0, sizeof visited);
    memset(ver, 0, sizeof ver);
    memset(hor, 0, sizeof hor);
}

bool outside(int x, int y) {
    return x < 0 || y < 0 || x > 501 || y > 501;
}

int first, last;
int qu[MN*MN], qv[MN*MN];

void go(int x, int y) {
    ++last;
    qu[last] = x;
    qv[last] = y;
    visited[x][y] = 1;
}

void bfs() {
    while (first <= last) {
        int x = qu[first], y = qv[first]; ++first;
        int xx, yy;

        // x-1
        xx = x - 1; yy = y;
        if (!outside(xx, yy) && !visited[xx][yy] && !ver[x][y]) {
            go(xx, yy);
        }
        // x+1
        xx = x + 1; yy = y;
        if (!outside(xx, yy) && !visited[xx][yy] && !ver[x+1][y]) {
            go(xx, yy);
        }
        // y-1
        xx = x; yy = y - 1;
        if (!outside(xx, yy) && !visited[xx][yy] && !hor[x][y]) {
            go(xx, yy);
        }
        // y+1
        xx = x; yy = y + 1;
        if (!outside(xx, yy) && !visited[xx][yy] && !hor[x][y+1]) {
            go(xx, yy);
        }
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int wall;
    while (GI(wall) == 1) {
        init();

        FOR(i,1,wall) {
            int x1, y1, x2, y2;
            GI(x1); GI(y1); GI(x2); GI(y2);
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);

            if (x1 == x2) {
                FOR(y,y1,y2-1) ver[x1][y] = 1;
            }
            else {
                FOR(x,x1,x2-1) hor[x][y1] = 1;
            }
        }
        first = last = 1;
        qu[1] = qv[1] = 0;
        visited[0][0] = 1;
        bfs();
        int cur = last;

        GI(wall);
        FOR(i,1,wall) {
            int x1, y1, x2, y2;
            GI(x1); GI(y1); GI(x2); GI(y2);
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);

            if (x1 == x2) {
                FOR(y,y1,y2-1) ver[x1][y] = 0;
            }
            else {
                FOR(x,x1,x2-1) hor[x][y1] = 0;
            }
        }

        memset(visited, 0, sizeof visited);
        first = last = 1;
        qu[1] = qv[1] = 0;
        visited[0][0] = 1;
        bfs();

        cout << last - cur << endl;
        break;
    }
}
