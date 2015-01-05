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
char a[MN][MN];
int qu[MN*MN], qv[MN*MN], first, last;
bool visited[MN][MN];

void go(int u, int v) {
    memset(visited, 0, sizeof visited);
    visited[u][v] = true;

    first = last = 1;
    qu[1] = u; qv[1] = v;
    while (first <= last) {
        u = qu[first], v = qv[first]; ++first;
        FOR(di,-1,1) FOR(dj,-1,1)
            if (di*di + dj*dj == 1) {
                int uu = u + di, vv = v + dj;
                if (a[uu][vv] == '.' && !visited[uu][vv]) {
                    visited[uu][vv] = true;
                    ++last;
                    qu[last] = uu; qv[last] = vv;
                }
            }
    }
}

void bfs(int m, int n) {
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
        go(i, j);
        return ;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int m, n, k;
    while (cin >> m >> n >> k) {
        memset(a, '#', sizeof a);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        bfs(m, n);

        FOR(i,last-k+1,last) a[qu[i]][qv[i]] = 'X';
        FOR(i,1,m) {
            FOR(j,1,n) cout << a[i][j];
            cout << "\n";
        }
    }
    return 0;
}
