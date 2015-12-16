
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 111;

int m, n;
char a[MN][MN];
int visited[MN][MN];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> m >> n) {
        memset(a, '.', sizeof a);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        queue<int> qu, qv;
        memset(visited, -1, sizeof visited);
        FOR(i,0,m+1) FOR(j,0,n+1) if (a[i][j] == '.') {
            visited[i][j] = 0;
            qu.push(i);
            qv.push(j);
        }

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            int v = qv.front(); qv.pop();
            REP(dir,4) {
                int uu = u + di[dir], vv = v + dj[dir];
                if (uu < 1 || uu > m || vv < 1 || vv > n) continue;
                if (visited[uu][vv] >= 0) continue;

                visited[uu][vv] = visited[u][v] + 1;
                qu.push(uu);
                qv.push(vv);
            }
        }

        int ln = 0;
        FOR(i,1,m) FOR(j,1,n) ln = max(ln, visited[i][j]);

        int w = (ln < 10) ? 2 : 3;

        FOR(i,1,m) FOR(j,1,n) {
            if (a[i][j] == '.') cout << setw(w) << setfill('.') << '.';
            else cout << setw(w) << setfill('.') << visited[i][j];

            if (j == n) cout << '\n';
        }
        cout << endl;
    }
}
