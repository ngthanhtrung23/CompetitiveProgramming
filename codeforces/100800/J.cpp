
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int m, n, nPath;
pair<int,int> start, target;
char a[66][66];
bool has[122][66][66], blocked[122][66][66];
int d[122][66][66];

pair<int,int> readPair() {
    pair<int,int> res;
    char c;
    cin >> c;
    cin >> res.first >> res.second;
    cin >> c;
    return res;
}


struct Path {
    int n;
    pair<int,int> x[11];

    void read() {
        cin >> n;
        REP(i,n) x[i] = readPair();
    }

    void block() {
        int u = 0, dir = 1;
        REP(time,120) {
            has[time][x[u].first][x[u].second] = true;

            if (n == 1) continue;

            u += dir;
            if (u >= n || u < 0) {
                u -= dir;
                dir = -dir;
                u += dir;
            }
        }
    }
} paths[222];

bool outside(int u, int v) {
    return u < 1 || u > m || v < 1 || v > n;
}

const int di[5] = {-1,1,0,0,0};
const int dj[5] = {0,0,-1,1,0};

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        start = readPair();
        target = readPair();
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        cin >> nPath;
        memset(blocked, 0, sizeof blocked);
        memset(has, 0, sizeof has);
        FOR(i,1,nPath) {
            paths[i].read();
            paths[i].block();
        }
        REP(t,120) {
            FOR(i,1,m) FOR(j,1,n)
                if (has[t][i][j]) {
                    blocked[t][i][j] = true;
                    FORD(ii,i-1,1) {
                        if (a[ii][j] == '#') break;
                        blocked[t][ii][j] = true;
                    }
                    FOR(ii,i+1,m) {
                        if (a[ii][j] == '#') break;
                        blocked[t][ii][j] = true;
                    }
                    FORD(jj,j-1,1) {
                        if (a[i][jj] == '#') break;
                        blocked[t][i][jj] = true;
                    }
                    FOR(jj,j+1,n) {
                        if (a[i][jj] == '#') break;
                        blocked[t][i][jj] = true;
                    }
                }
        }
        queue<int> qu, qv, qt;
        memset(d, -1, sizeof d);
        qu.push(start.first);
        qv.push(start.second);
        qt.push(0);
        d[0][start.first][start.second] = 0;

        try {
            while (!qu.empty()) {
                int u = qu.front(); qu.pop();
                int v = qv.front(); qv.pop();
                int t = qt.front(); qt.pop();

                if (make_pair(u, v) == target) {
                    cout << d[t][u][v] << endl;
                    throw 1;
                }

                REP(dir,5) {
                    int uu = u + di[dir];
                    int vv = v + dj[dir];
                    int tt = (t + 1) % 120;

                    if (outside(uu, vv)) continue;
                    if (a[uu][vv] == '#') continue;

                    if (make_pair(uu, vv) == target) {
                        cout << d[t][u][v] + 1 << endl;
                        throw 1;
                    }

                    if (blocked[tt][uu][vv]) continue;
                    if (d[tt][uu][vv] >= 0) continue;

                    d[tt][uu][vv] = d[t][u][v] + 1;
                    qu.push(uu);
                    qv.push(vv);
                    qt.push(tt);
                }
            }
            cout << "IMPOSSIBLE" << endl;
        }
        catch(int e) {
        }
    }
}

