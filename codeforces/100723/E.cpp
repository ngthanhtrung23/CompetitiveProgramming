
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
int n, X, Y, startx, starty, targetx, targety, x[10111], y[10111];
int d[MN][MN], visited[MN][MN];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

void init() {
    queue<int> qu, qv;
    FOR(i,1,n) {
        d[x[i]][y[i]] = 0;
        qu.push(x[i]);
        qv.push(y[i]);
    }

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 0 || vv < 0 || uu >= X || vv >= Y) continue;
            if (d[uu][vv] >= 0) continue;

            d[uu][vv] = d[u][v] + 1;
            qu.push(uu);
            qv.push(vv);
        }
    }
//    REP(i,X) {
//        PR0(d[i], Y);
//    }
}

bool check(int val) {
    if (d[startx][starty] < val) return false;
    if (d[targetx][targety] < val) return false;

    memset(visited, -1, sizeof visited);
    visited[startx][starty] = 0;
    queue<int> qu, qv;
    qu.push(startx);
    qv.push(starty);

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 0 || vv < 0 || uu >= X || vv >= Y) continue;
            if (d[uu][vv] < val) continue;
            if (visited[uu][vv] >= 0) continue;

            visited[uu][vv] = visited[u][v] + 1;
            qu.push(uu);
            qv.push(vv);
        }
    }
    return visited[targetx][targety] >= 0;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> X >> Y;
        cin >> startx >> starty >> targetx >> targety;
        FOR(i,1,n) cin >> x[i] >> y[i];

        memset(d, -1, sizeof d);
        init();

        int l = 0, r = 2011, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        check(res);
        cout << res << ' ' << visited[targetx][targety] << '\n';
    }
}

