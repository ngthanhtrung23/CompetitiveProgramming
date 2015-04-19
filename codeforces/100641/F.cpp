
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

const int INF = 1000111;
pair<int,char> a[111][111];
int m, n;
int distFromStart[111][111];
int distToEnd[111][111];

pair<int,int> go(int u, int v, int step, char c) {
    int uu = u, vv = v;
    switch (c) {
        case 'E':
            vv += step;
            break;
        case 'W':
            vv -= step;
            break;
        case 'N':
            uu -= step;
            break;
        case 'S':
            uu += step;
            break;
    }
    return make_pair(uu, vv);
}

pair<int,int> go(int u, int v) {
    return go(u, v, a[u][v].first, a[u][v].second);
}

bool outside(int u, int v) {
    return u < 1 || u > m || v < 1 || v > n;
}

void dfs(int u, int v, int d) {
    distFromStart[u][v] = d;
    if (u == m && v == n) return;

    int uu, vv;
    auto t = go(u, v);
    uu = t.first, vv = t.second;

    if (!outside(uu, vv) && distFromStart[uu][vv] < 0) {
        dfs(uu, vv, d + 1);
    }
}

bool calculating[111][111];

int dp(int u, int v) {
    if (u == m && v == n) return distToEnd[u][v] = 0;
    if (distToEnd[u][v] >= 0) return distToEnd[u][v];

    calculating[u][v] = true;

    int uu, vv;
    auto t = go(u, v);
    uu = t.first, vv = t.second;
    if (outside(uu, vv)) return distToEnd[u][v] = INF;

    if (calculating[uu][vv]) {
        distToEnd[u][v] = INF;
    }
    else {
        int t = dp(uu, vv);
        if (t == INF) distToEnd[u][v] = INF;
        else distToEnd[u][v] = t + 1;
    }

    calculating[u][v] = false;

    return distToEnd[u][v];
}

int bestl, saveu, savev, new_val;
char new_dir;

void update(int l, int u, int v, int val, char dir) {
    if (make_pair(l, make_pair(make_pair(u, v), make_pair(val, dir)))
            < make_pair(bestl, make_pair(make_pair(saveu, savev), make_pair(new_val, new_dir)))) {
        bestl = l;
        saveu = u;
        savev = v;
        new_val = val;
        new_dir = dir;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> m >> n && m && n) {
        FOR(i,1,m) FOR(j,1,n) {
            if (i == m && j == n) continue;
            int u; char c; cin >> u >> c;
            a[i][j] = make_pair(u, c);
        }
//        FOR(i,1,m) {
//            FOR(j,1,n) cout << a[i][j].first << a[i][j].second << ' ';
//            cout << endl;
//        }
        memset(distFromStart, -1, sizeof distFromStart);
        dfs(1, 1, 0);
//        FOR(i,1,m) {
//            PR(distFromStart[i], n);
//        }
//        DEBUG("=====");

        memset(distToEnd, -1, sizeof distToEnd);
        memset(calculating, 0, sizeof calculating);
        FOR(i,1,m) FOR(j,1,n) {
            if (distToEnd[i][j] < 0) {
                dp(i, j);
            }
        }

//        FOR(i,1,m) {
//            PR(distToEnd[i], n);
//        }
        
        // Find optimal change
        bestl = INF;
        saveu = -1, savev = -1;
        new_val = -1;
        new_dir = ' ';

        FOR(i,1,m) FOR(j,1,n) {
            // assume we change this cell
            if (distFromStart[i][j] < 0) continue;

            FOR(ii,1,m) if (ii != i && distToEnd[ii][j] < INF) {
                int step; char dir;
                if (ii < i) dir = 'N', step = i - ii;
                else dir = 'S', step = ii - i;

                int l = distFromStart[i][j] + 1 + distToEnd[ii][j];
                update(l, i, j, step, dir);
            }

            FOR(jj,1,n) if (jj != j && distToEnd[i][jj] < INF) {
                int step; char dir;
                if (jj < j) dir = 'W', step = j - jj;
                else dir = 'E', step = jj - j;

                int l = distFromStart[i][j] + 1 + distToEnd[i][jj];
                update(l, i, j, step, dir);
            }
        }

        cout << "Case " << ++test << ": ";
        if (bestl == INF) cout << "impossible" << endl;
        else if (distFromStart[m][n] >= 0 && distFromStart[m][n] <= bestl)
            cout << "none " << distFromStart[m][n] << endl;
        else {
            cout << saveu-1 << ' ' << savev-1 << ' ' << new_val << new_dir << ' ' << bestl << endl;
        }
    }
    return 0;
}
