
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

char a[111][11][11];
bool visited[111][11][11];

bool bfs() {
    memset(visited, false, sizeof visited);
    visited[0][8][1] = true;
    queue< pair<int, pair<int,int> > > qu;
    qu.push(make_pair(0, make_pair(8, 1)));

    while (!qu.empty()) {
        int t = qu.front().first, u = qu.front().second.first, v = qu.front().second.second;
        qu.pop();
        if (u == 1 && v == 8) return true;
        if (t == 30) continue;

        FOR(di,-1,1) FOR(dj,-1,1) {
            int uu = u + di, vv = v + dj;
            if (uu < 1 || uu > 8 || vv < 1 || vv > 8) continue;
            if (a[t][uu][vv] == 'S' || a[t+1][uu][vv] == 'S') continue;
            if (visited[t+1][uu][vv]) continue;

            visited[t+1][uu][vv] = true;
            qu.push(make_pair(t+1, make_pair(uu, vv)));
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a[0][1][1]) {
        FOR(i,1,8) FOR(j,1,8) if (i > 1 || j > 1) cin >> a[0][i][j];

        a[0][1][8] = a[0][8][1] = '.';

        FOR(time,1,32) {
            FOR(i,1,8) FOR(j,1,8) {
                if (i == 1) a[time][i][j] = '.';
                else a[time][i][j] = a[time-1][i-1][j];
            }
        }

        cout << (bfs() ? "WIN" : "LOSE") << endl;
    }
    return 0;
}

