
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 55;
char a[MN][MN];
int m, n;
int visited[MN][MN];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1,};

void bfs(int u, int v) {
    queue<int> qu, qv;
    qu.push(u);
    qv.push(v);
    visited[u][v] = true;

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (a[uu][vv] != '#' && !visited[uu][vv]) {
                qu.push(uu); qv.push(vv);
                visited[uu][vv] = true;
            }
        }
    }
}

void bfs() {
    memset(visited, 0, sizeof visited);
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
        bfs(i, j);
        return;
    }
}

bool vis2[MN][MN];

void bfs2(int i, int j, int badu, int badv) {
    queue<int> qu, qv;
    qu.push(i); qv.push(j);
    vis2[i][j] = true;

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu == badu && vv == badv) continue;
            if (vis2[uu][vv]) continue;

            if (a[uu][vv] == '.'
                    || (a[uu][vv] == '?' && visited[uu][vv])) {
                vis2[uu][vv] = true;
                qu.push(uu);
                qv.push(vv);
            }
        }
    }
}

bool check(int u, int v) {
    memset(vis2, 0, sizeof vis2);
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
        bfs2(i, j, u, v);

        FOR(ii,1,m) FOR(jj,1,n) if (a[ii][jj] == '.' && !vis2[ii][jj]) return false;

        return true;
    }
    return false;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        memset(a, '#', sizeof a);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        bfs();

        bool bad = false;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.' && !visited[i][j]) bad = true;
        if (bad) {
            cout << "Impossible" << endl;
            continue;
        }

        bad = false;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '?' && visited[i][j]) {
            if (check(i, j)) {
                bad = true;
                break;
            }
        }
        if (bad) {
            cout << "Ambiguous" << endl;
            continue;
        }

        FOR(i,1,m) FOR(j,1,n) {
            if (a[i][j] == '?') {
                if (visited[i][j]) cout << '.';
                else cout << '#';
            }
            else cout << a[i][j];
            if (j == n) cout << endl;
        }
    }
}
