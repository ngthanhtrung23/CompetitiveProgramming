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

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

int n, m, r, c[66][66][66];
int f[66][66][66];

int main() {
    while (scanf("%d%d%d", &n, &m, &r) == 3) {
        FOR(k,1,m) {
            FOR(i,1,n) FOR(j,1,n) scanf("%d", &c[k][i][j]);
            FOR(x,1,n)
                FOR(i,1,n) FOR(j,1,n)
                    c[k][i][j] = min(c[k][i][j], c[k][i][x] + c[k][x][j]);
        }

        FOR(i,1,n) FOR(j,1,n) {
            f[0][i][j] = c[1][i][j];

            FOR(k,2,m)
                f[0][i][j] = min(f[0][i][j], c[k][i][j]);
        }

        FOR(t,1,60) {
            FOR(i,1,n) FOR(j,1,n) {
                f[t][i][j] = f[t-1][i][j];

                FOR(x,1,n)
                    f[t][i][j] = min(f[t][i][j], f[t-1][i][x] + f[0][x][j]);
            }
        }

        while (r--) {
            int s, t, k; scanf("%d%d%d", &s, &t, &k);
            if (k > 60) k = 60;
            printf("%d\n", f[k][s][t]);
        }
    }
    return 0;
}
