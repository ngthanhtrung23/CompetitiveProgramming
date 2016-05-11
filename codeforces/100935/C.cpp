
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

int m, n;
char a[33][33];
bool visited[33][33];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

void bfs(int u, int v) {
    visited[u][v] = 1;
    queue<int> qu, qv;
    qu.push(u); qv.push(v);

    while (!qu.empty()) {
        u = qu.front(); qu.pop();
        v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 0 || uu > m || vv < 0 || vv > n) continue;
            if (visited[uu][vv]) continue;
            if (a[uu][vv] == '*') continue;

            qu.push(uu);
            qv.push(vv);
            visited[uu][vv] = 1;
        }
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> m >> n;
        memset(a, '.', sizeof a);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        ++m; ++n;

        int cnt = 0;

        memset(visited, 0, sizeof visited);
        FOR(i,0,m) FOR(j,0,n) if (a[i][j] == '.' && !visited[i][j]) {
            ++cnt;
            bfs(i, j);
        }

        cout << "Case " << test << ": " << (cnt == 2 ? "Zero" : "Eight") << endl;
    }
}
