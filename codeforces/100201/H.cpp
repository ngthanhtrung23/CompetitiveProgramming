#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define write write__
#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

int visited[111][111][2], n, s;
int to[111][111], write[111][111], dir[111][111];

int first, last, qu[111*222], qv[111*222], qf[111*222];

bool bfs() {
    memset(visited, false, sizeof visited);

    first = last = 1;
    qu[1] = 1; qv[1] = 0; qf[1] = 0;
    visited[1][0][0] = true;

    while (first <= last) {
        int u = qu[first], v = qv[first], f = qf[first]; ++first;
        if (u == n) continue;

        int from, there;
        if (v == 0) {
            from = 1, there = s;
            if (f) from = there = s;
        } else {
            from = there = v;
        }

        FOR(add,from,there) {
            if (dir[u][add] == -1) return false;

            int uu = to[u][add];
            int vv, ff = f;
            if (!v && add == s) ff = 1;

            if (dir[u][add] == 0) vv = write[u][add]; else vv = 0;

            if (visited[uu][vv][ff]) continue;

            visited[uu][vv][ff] = true;
            ++last;
            qu[last] = uu;
            qv[last] = vv;
            qf[last] = ff;
        }
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("left.in", "r", stdin);
    freopen("left.out", "w", stdout);

    while (cin >> n >> s) {
        FOR(i,1,n-1) FOR(j,1,s) cin >> to[i][j] >> write[i][j] >> dir[i][j];
        cout << (bfs() ? "YES" : "NO") << endl;
    }
}