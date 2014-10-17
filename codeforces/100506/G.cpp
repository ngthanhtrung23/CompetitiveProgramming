#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

char a[111][111];
double f[111][111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int test; cin >> test;
    while (test--) {
        double res = 0.0;
        int m, n; cin >> m >> n;
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        FOR(col,1,n) {
            double cur = 0.0;
            FOR(i,1,m) FOR(j,1,n) f[i][j] = 0.0;

            f[1][col] = 1.0;
            FOR(i,1,m) FOR(j,1,n)
                if (f[i][j] > 1e-9) {
                    if (a[i][j] >= '1' && a[i][j] <= '9')
                        cur += f[i][j] * (a[i][j] - '0');
                    else if (a[i][j] == '*') {
                        f[i+1][j-1] += f[i][j] / 2.0;
                        f[i+1][j+1] += f[i][j] / 2.0;
                    } else f[i+1][j] += f[i][j];
                }
            res = max(res, cur);
        }

        cout << (fixed) << setprecision(9) << res << endl;
    }
    return 0;
}
