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

int n;
string a[250111];
int f[250011][4][4][4][4];

int decode(char c) {
    switch (c) {
        case 'B': return 0;
        case 'G': return 1;
        case 'R': return 2;
        case 'Y': return 3;
        default: cout << ":@)" << endl; return -1;
    }
}

char tmp[111];
const int oo = 1000111000;

inline int getScore(int color, int s, int x) {
    switch (color) {
        case 0: return s - x;
        case 1: return s + x;
        case 2: return s * x;
        case 3: return (x) ? (s / x) : 0;
        default: cout << ":@)" << endl; return -1;
    }
}

int res;
inline void update(int &x, int val) {
    if (val > x) x = val;
}

int score[4][4];

int main() {
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        scanf("%d\n", &n);
        FOR(i,1,n) {
            gets(tmp);
            a[i] = string(tmp);
        }
        REP(t,n+1) REP(x,4) REP(y,4) REP(z,4) REP(w,4) f[t][x][y][z][w] = -oo;
        res = -oo;

        int x[4] = {
            decode(a[1][0]),
            decode(a[1][2]),
            decode(a[1][4]),
            decode(a[1][6])
        };
        sort(x, x+4);

        f[1][x[0]][x[1]][x[2]][x[3]] = 0;

        FOR(i,2,n) REP(x0,4) FOR(x1,x0,3) FOR(x2,x1,3) FOR(x3,x2,3) if (f[i-1][x0][x1][x2][x3] > -oo) {
            int y[4], z[4], x[4] = {x0, x1, x2, x3};
            y[0] = decode(a[i][0]), z[0] = a[i][1] - '0';
            y[1] = decode(a[i][2]), z[1] = a[i][3] - '0';
            y[2] = decode(a[i][4]), z[2] = a[i][5] - '0';
            y[3] = decode(a[i][6]), z[3] = a[i][7] - '0';
            int s = z[0] + z[1] + z[2] + z[3];

            int ff = f[i-1][x0][x1][x2][x3];
            update(f[i][x0][x1][x2][x3], ff - s);

            REP(to,4) REP(add,4) if (x[to] == y[add]) {
                int xx[4] = {x[0], x[1], x[2], x[3]};
                xx[to] = y[(add + 2) % 4];
//                sort(xx, xx+4);
                int changed = to;
                while (changed < 3 && xx[changed] > xx[changed+1]) {
                    swap(xx[changed], xx[changed+1]);
                    ++changed;
                }
                while (changed > 0 && xx[changed] < xx[changed-1]) {
                    swap(xx[changed], xx[changed-1]);
                    --changed;
                }
                update(f[i][xx[0]][xx[1]][xx[2]][xx[3]], ff + getScore(x[to], s, z[add]));
            }
        }
        res = -oo;
        REP(x,4) REP(y,4) REP(z,4) REP(t,4) {
            update(res, f[n][x][y][z][t]);
        }
        cout << res << endl;
    }
    return 0;
}
