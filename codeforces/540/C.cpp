
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

const int MN = 511;

int m, n;
char a[MN][MN];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
pair<int,int> trace[MN][MN];

bool outside(int u, int v) {
    return u < 1 || u > m || v < 1 || v > n;
}

bool bfs(int startu, int startv, int targetu, int targetv) {
    queue< pair<int,int> > qu;
    qu.push(make_pair(startu, startv));

    memset(trace, -1, sizeof trace);
    trace[startu][startv] = make_pair(0, 0);

    while (!qu.empty()) {
        int u = qu.front().first, v = qu.front().second; qu.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu == targetu && vv == targetv) return true;

            if (outside(uu, vv) || a[uu][vv] == 'X') continue;
            if (trace[uu][vv].first < 0) {

                trace[uu][vv] = make_pair(u, v);
                qu.push(make_pair(uu, vv));
            }
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        FOR(i,1,m) {
            string s; cin >> s;
            FOR(j,1,n) a[i][j] = s[j-1];
        }

        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;

        if (a[r2][c2] == 'X') {
            memset(trace, -1, sizeof trace);
            if (bfs(r1, c1, r2, c2)) cout << "YES"; else cout << "NO";
            cout << endl;
        }
        else {
            memset(trace, -1, sizeof trace);

            int ke = 0;
            REP(dir,4) {
                int u = r2 + di[dir], v = c2 + dj[dir];
                if (!outside(u, v) && a[u][v] == '.') ++ke;
                if (u == r1 && v == c1) ++ke;
            }

            if (bfs(r1, c1, r2, c2) && ke >= 2) cout << "YES"; else cout << "NO";
            cout << endl;
        }
    }
    return 0;
}
