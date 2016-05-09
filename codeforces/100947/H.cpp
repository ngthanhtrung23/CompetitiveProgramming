
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

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 111;
int m, n;
int f[MN][MN];
char a[MN][MN];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

void bfs1() {
    memset(f, -1, sizeof f);
    queue<int> qu, qv;

    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '*') {
        f[i][j] = 1;
        qu.push(i);
        qv.push(j);
    }

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (f[uu][vv] >= 0 || a[uu][vv] == '#') continue;

            f[uu][vv] = f[u][v] + 1;
            qu.push(uu);
            qv.push(vv);
        }
    }

    FOR(i,1,m) FOR(j,1,n) if (f[i][j] < 0) f[i][j] = 1000111000;
}

int g[MN][MN];
bool bfs2() {
    queue<int> qu, qv;
    memset(g, -1, sizeof g);
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'S') {
        g[i][j] = 1;
        qu.push(i);
        qv.push(j);
    }
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();
        if (a[u][v] == 'X') return 1;

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (a[uu][vv] == '#') continue;
            if (g[uu][vv] >= 0) continue;
            if (g[u][v] + 1 >= f[uu][vv]) continue;

            g[uu][vv] = g[u][v] + 1;
            qu.push(uu);
            qv.push(vv);
        }
    }
    return false;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> m >> n;
        memset(a, '#', sizeof a);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        bfs1();
        cout << (bfs2() ? "yes" : "no") << '\n';
    }
}
