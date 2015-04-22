
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

const int MN = 2511;

int m, n;
char a[MN][MN];
#define left __left
#define right __right
int up[MN][MN], left[MN][MN];

void init() {
    FOR(i,1,m) FOR(j,1,n) {
        if (a[i][j] == '#') {
            up[i][j] = i;
            left[i][j] = j;
        }
        else {
            up[i][j] = up[i-1][j];
            left[i][j] = left[i][j-1];
        }
    }
}

#define max(x, y) ((x > y) ? (x) : (y))
#define min(x, y) ((x < y) ? (x) : (y))

bool check(int u, int v, int x, int y) {
    if (u == x) {
        if (left[u][max(v, y)] < min(v, y)) return true;
    }
    if (v == y) {
        if (up[max(u, x)][v] < min(u, x)) return true;
    }
    return false;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        init();
        int q; scanf("%d\n", &q);
        while (q--) {
            int r1, c1, r2, c2; scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
            if (a[r1][c1] == '#' || a[r2][c2] == '#') puts("NO");
            else if (check(r1, c2, r1, c1) && check(r1, c2, r2, c2)) puts("YES");
            else if (check(r2, c1, r1, c1) && check(r2, c1, r2, c2)) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}

