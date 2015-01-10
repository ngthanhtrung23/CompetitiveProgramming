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

const int di[4] = {-1, 1, 0, 0};
const int dj[4] = {0, 0, -1, 1};

int m, n, f[1011][1011];
char a[1011][1011];
bool hasCycle;

bool can(char a, char b) {
    return (a == 'D' && b == 'I')
        || (a == 'I' && b == 'M')
        || (a == 'M' && b == 'A')
        || (a == 'A' && b == 'D');
}

void dfs(int u, int v) {
    if (hasCycle) return ;
    if (f[u][v] == -2) {
        hasCycle = true;
        return ;
    }
    if (f[u][v] > 0) return ;

    f[u][v] = -2;
    int res = 1;

    REP(dir,4) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (can(a[u][v], a[uu][vv])) {
            dfs(uu, vv);
            if (hasCycle) return ;

            res = max(res, f[uu][vv] + 1);
        }
    }

    f[u][v] = res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        memset(a, ' ', sizeof a);

        string tmp;
        FOR(i,1,m) {
            cin >> tmp;
            FOR(j,1,n) a[i][j] = tmp[j-1];
        }

        hasCycle = false;
        memset(f, -1, sizeof f);
        FOR(i,1,m) FOR(j,1,n)
            if (a[i][j] == 'D' && f[i][j] == -1) {
                dfs(i, j);
            }

        if (hasCycle) cout << "Poor Inna!";
        else {
            int res = 0;
            FOR(i,1,m) FOR(j,1,n)
                if (a[i][j] == 'D')
                    res = max(res, f[i][j]);
            while (res % 4) --res;
            if (res == 0) cout << "Poor Dima!";
            else cout << res / 4;
        }
        cout << endl;
    }
    return 0;
}

