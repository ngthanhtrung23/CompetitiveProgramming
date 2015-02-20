
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

int m, n;
char a[1011][1011];
int visited[1011][1011];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        queue< pair<int,int> > qu;
        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        memset(visited, -1, sizeof visited);
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'E') {
            qu.push(make_pair(i, j));
            visited[i][j] = 0;
        }

        while (!qu.empty()) {
            int u = qu.front().first, v = qu.front().second;
            qu.pop();
            REP(dir,4) {
                int uu = u + di[dir], vv = v + dj[dir];
                if (uu > 0 && uu <= m && vv > 0 && vv <= n && a[uu][vv] != 'T' && visited[uu][vv] < 0) {
                    qu.push(make_pair(uu, vv));
                    visited[uu][vv] = visited[u][v] + 1;
                }
            }
        }
        int len = -1;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'S') len = visited[i][j];
        int res = 0;
        FOR(i,1,m) FOR(j,1,n)
            if (a[i][j] >= '0' && a[i][j] <= '9')
                if (visited[i][j] <= len && visited[i][j] >= 0)
                    res += a[i][j] - '0';
        cout << res << endl;
    }
    return 0;
}

