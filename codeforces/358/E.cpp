
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

int m, n;
int a[MN][MN], sum[MN][MN];
pair<int,int> start;

int getSum(int i1, int j1, int i2, int j2) {
    if (i1 > i2) swap(i1, i2);
    if (j1 > j2) swap(j1, j2);
    return sum[i2][j2]
        - sum[i1-1][j2]
        - sum[i2][j1-1]
        + sum[i1-1][j1-1];
}

pair<int,int> getStart() {
    FOR(i,1,m) FOR(j,1,n)
        if (getSum(i, j, i, j) == 1) {
            return make_pair(i, j);
        }
    assert(false);
}

int first, last;
int qu[MN*MN], qv[MN*MN];
int visited[MN][MN];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

bool outside(int u, int v) {
    return u < 1 || u > m || v < 1 || v > n;
}

bool bfs() {
    memset(visited, 0, sizeof visited);
    first = last = 1;
    qu[1] = start.first;
    qv[1] = start.second;
    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (outside(uu, vv) || a[uu][vv] == 0 || visited[uu][vv]) continue;

            visited[uu][vv] = 1;
            ++last;
            qu[last] = uu;
            qv[last] = vv;
        }
    }
    FOR(i,1,m) FOR(j,1,n)
        if (a[i][j] && !visited[i][j]) {
            return false;
        }
    return true;
}

void resetVisited() {
    FOR(i,1,last) {
        int u = qu[i], v = qv[i];
        visited[u][v] = 0;
    }
}

bool check(int len) {
    first = last = 1;
    qu[1] = start.first;
    qv[1] = start.second;
    visited[start.first][start.second] = 1;

    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (outside(uu, vv) || a[uu][vv] == 0) continue;

            uu = u + di[dir] * len, vv = v + dj[dir] * len;

            if (outside(uu, vv)) return false;
            if (getSum(u, v, uu, vv) != len+1) return false;

            if (visited[uu][vv]) continue;
            visited[uu][vv] = 1;
            ++last;
            qu[last] = uu;
            qv[last] = vv;
        }
    }
    int odd = 0;
    FOR(i,1,last) {
        int u = qu[i], v = qv[i];
        int deg = 0;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (outside(uu, vv) || a[uu][vv] == 0) continue;
            ++deg;
        }

        if (deg % 2 == 1) ++odd;
    }
    if (odd != 0 && odd != 2) return false;

    FOR(i,1,last) {
        int u = qu[i], v = qv[i];
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (outside(uu, vv) || a[uu][vv] == 0) continue;
            
            uu = u + di[dir] * len;
            vv = v + dj[dir] * len;

            FOR(x,min(u,uu),max(u,uu))
                FOR(y,min(v,vv),max(v,vv))
                    visited[x][y] = 1;
        }
    }
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] && !visited[i][j]) {
        memset(visited, 0, sizeof visited);
        return false;
    }
    memset(visited, 0, sizeof visited);
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &m, &n) == 2) {
        FOR(i,1,m) FOR(j,1,n) {
            scanf("%d", &a[i][j]);
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i][j];
        }
        start = getStart();

        if (!bfs()) {
            cout << -1 << endl;
            continue;
        }
        memset(visited, 0, sizeof visited);

        bool good = false;
        FOR(res,2,min(m-1,n-1)) {
            if (check(res)) {
                good = true;
                cout << res << ' ';
            }
            resetVisited();
        }
        if (!good) cout << -1;
        cout << endl;
    }
}

