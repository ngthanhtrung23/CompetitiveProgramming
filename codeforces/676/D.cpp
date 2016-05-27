#include <bits/stdc++.h>
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

int UP = 1<<3;
int RIGHT = 1<<2;
int DOWN = 1<<1;
int LEFT = 1<<0;
int ALL = UP + RIGHT + DOWN + LEFT;
int m, n;

int conv(char c) {
    if (c == '+') return ALL;
    if (c == '-') return LEFT + RIGHT;
    if (c == '|') return UP + DOWN;
    if (c == '^') return UP;
    if (c == 'v') return DOWN;
    if (c == '<') return LEFT;
    if (c == '>') return RIGHT;
    if (c == 'L') return ALL - LEFT;
    if (c == 'R') return ALL - RIGHT;
    if (c == 'D') return ALL - DOWN;
    if (c == 'U') return ALL - UP;
    return 0;
}

bool outside(int u, int v) {
    return u < 0 || v < 0 || u > m || v > n;
}

int a[1011][1011];
int f[1011][1011][4];

int rot(int x) {
    return (x >> 1) + ((x & 1) << 3);
}

int rot(int x, int times) {
    while (times--) x = rot(x);
    return x;
}

const int di[4] = {1,-1,0,0};
const int dj[4] = {0,0,1,-1};

int canGo(int u, int v, int d, int uu, int vv, int dir) {
    int fr = rot(a[u][v], d);
    int to = rot(a[uu][vv], d);

    if (dir == 1) { // DOWN
        return (fr & UP) && (to & DOWN);
    }
    if (dir == 0) { // UP
        return (fr & DOWN) && (to & UP);
    }
    if (dir == 2) { // RIGHT
        return (fr & RIGHT) && (to & LEFT);
    }
    if (dir == 3) { // LEFT
        return (fr & LEFT) && (to & RIGHT);
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) {
            char c; cin >> c;
            a[i][j] = conv(c);
        }
        queue<int> qu, qv, qd;
        int startu, startv;
        int targetu, targetv;
        cin >> startu >> startv;
        cin >> targetu >> targetv;

        qu.push(startu);
        qv.push(startv);
        qd.push(0);
        memset(f, -1, sizeof f);
        f[startu][startv][0] = 0;

        int res = -1;
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            int v = qv.front(); qv.pop();
            int d = qd.front(); qd.pop();

            if (u == targetu && v == targetv) {
                res = f[u][v][d];
                break;
            }
            
            // next dir
            int uu = u, vv = v, dd = (d + 1) % 4;
            if (f[uu][vv][dd] < 0) {
                f[uu][vv][dd] = f[u][v][d] + 1;
                qu.push(uu);
                qv.push(vv);
                qd.push(dd);
            }

            // move in 4 directions
            REP(dir,4) {
                uu = u + di[dir], vv = v + dj[dir], dd = d;
                if (outside(uu, vv)) continue;

                if (canGo(u, v, d, uu, vv, dir) && f[uu][vv][dd] < 0) {
                    f[uu][vv][dd] = f[u][v][d] + 1;
                    qu.push(uu);
                    qv.push(vv);
                    qd.push(dd);
                }
            }
        }
        cout << res << endl;
    }
}
