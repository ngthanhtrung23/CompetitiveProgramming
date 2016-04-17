
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

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
int GI(int& x) {
    return scanf("%lld", &x);
}

int m, n;
vector<string> a;
vector<vector<int> > tru, trv;

void bfs(int i, int j) {
    queue<int> qu, qv;
    qu.push(i);
    qv.push(j);

    REP(u,m+2) REP(v,n+2) tru[u][v] = trv[u][v] = -1;
    tru[i][j] = i;
    trv[i][j] = j;

    while (!qu.empty()) {
        int u  = qu.front(); qu.pop();
        int v  = qv.front(); qv.pop();
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (a[uu][vv] != '#' && a[uu][vv] != 'P' && tru[uu][vv] < 0) {
                qu.push(uu);
                qv.push(vv);
                tru[uu][vv] = u;
                trv[uu][vv] = v;
            }
        }
    }
}

bool solve() {
//    FOR(i,1,m) cout << a[i] << endl;

    int startu, startv, targetu, targetv;
    FOR(i,1,m) FOR(j,1,n) {
        if (a[i][j] == '1') startu = i, startv = j;
        if (a[i][j] == '2') targetu = i, targetv = j;
    }
    if (tru[targetu][targetv] < 0) return false;

    int u = targetu, v = targetv;

    while (a[u][v] != '1') {
        if (a[u][v] == '.') a[u][v] = 'P';
        int uu = tru[u][v];
        int vv = trv[u][v];
        u = uu;
        v = vv;
    }
    if (a[u][v] == '.') a[u][v] = 'P';
    
//    cout << "--> " << endl; FOR(i,1,m) cout << a[i] << endl;

    // can avoid in middle of path
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'P') {
        REP(dir,4) {
            int ii = i + di[dir], jj = j + dj[dir];
            if (a[ii][jj] == '.') return true;
        }
    }
    // can avoid in starting positions
    REP(turn,2) {
        int i, j;
        if (turn == 0) i = startu, j = startv;
        else i = targetu, j = targetv;

        while (true) {
            int cnt = 0;
            int savei = -1, savej = -1;
            REP(dir,4) {
                int ii = i + di[dir], jj = j + dj[dir];
                if (a[ii][jj] == '.') {
                    ++cnt;
                    savei = ii;
                    savej = jj;
                }
            }
            if (cnt >= 2) return true;
            if (cnt == 0) break;

            if (a[i][j] == '.') a[i][j] = 'X';
            i = savei, j = savej;
        }

        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'X') a[i][j] = '.';
    }
    a[startu][startv] = a[targetu][targetv] = 'P';
    // can use different path
    REP(i,m+2) REP(j,n+2) tru[i][j] = trv[i][j] = -1;
    REP(dir,4) {
        int u = startu + di[dir], v = startv + dj[dir];
        if (a[u][v] == '.') bfs(u, v);
    }
    REP(dir,4) {
        int u = targetu + di[dir], v = targetv + dj[dir];
        if (a[u][v] == '.' && tru[u][v] >= 0) return true;
    }

    return false;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        string empty = "";
        REP(j,n+2) empty += '#';
        a.resize(m+2);
        a[0] = a[m+1] = empty;
        FOR(i,1,m) {
            cin >> a[i];
            a[i] = "#" + a[i] + "#";
        }
        tru.resize(m+2); trv.resize(m+2);
        REP(i,m+2) {
            tru[i].resize(n+2);
            trv[i].resize(n+2);
        }

        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '1') {
            bfs(i, j);
        }
        cout << (solve() ? "YES" : "NO") << endl;
    }
}
