#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

const int di[] = {0,1,0,-1};
const int dj[] = {1,0,-1,0};

char a[111][111];
int nu[111][111][4][2], nv[111][111][4][2], m, n, q;

void init() {
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] != '0') REP(dir,4) REP(cp,2) {
        nu[i][j][dir][cp] = i;
        nv[i][j][dir][cp] = j;
        int ii = i + di[dir], jj = j + dj[dir];
        while (ii > 0 && jj > 0 && ii <= m && jj <= n && a[ii][jj] == a[i][j]) {
            nu[i][j][dir][cp] = ii;
            nv[i][j][dir][cp] = jj;
            ii = ii + di[dir], jj = jj + dj[dir];
        }
        ii -= di[dir]; jj -= dj[dir];

        int dir2 = dir;
        if (cp == 0) dir2--; else dir2++;
        if (dir2 < 0) dir2 = 3; else if (dir2 > 3) dir2 = 0;

        ii = ii + di[dir2], jj = jj + dj[dir2];
        while (ii > 0 && jj > 0 && ii <= m && jj <= n && a[ii][jj] == a[i][j]) {
            nu[i][j][dir][cp] = ii;
            nv[i][j][dir][cp] = jj;
            ii = ii + di[dir2], jj = jj + dj[dir2];
        }
    }
}

int main() {
    scanf("%d%d\n", &m, &q);
    FOR(i,1,m) scanf("%s\n", &a[i][1]);
    n = 1;
    while (a[1][n+1] >= '0' && a[1][n+1] <= '9') n++;
//    cout << n << endl;

    init();

    int u = 1, v = 1, dp = 0, cp = 0;
    while (q--) {
        int uu = nu[u][v][dp][cp], vv = nv[u][v][dp][cp];
        uu = uu + di[dp], vv = vv + dj[dp];
        if (uu < 1 || vv < 1 || uu > m || vv > n || a[uu][vv] == '0') {
            if (cp == 0) cp = 1;
            else { // cp == 1
                cp = 0;
                dp = (dp + 1) % 4;
            }
        } else {
            u = uu; v = vv;
        }
//        cout << u << ' ' << v << ' ' << dp << ' ' << cp << endl;
    }
    printf("%d\n", a[u][v] - '0');
    return 0;
}