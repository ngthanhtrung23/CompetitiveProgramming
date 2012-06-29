#include <iomanip>
#include <sstream>
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int m, n, a[1011][1011], row[1011], col[1011];
ll fx[1011], fy[1011];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &m, &n) == 2) {
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        memset(fx, 0, sizeof fx);
        memset(fy, 0, sizeof fy);
        
        FOR(i,1,m) FOR(j,1,n) {
            scanf("%d", &a[i][j]);
            row[i] += a[i][j];
            col[j] += a[i][j];
        }
        FOR(i,0,m) {
            ll now = 2;
            for(int ii = i; ii >= 1; ii--) {
                fx[i] += row[ii] * now * now;
                now += 4;
            }
            now = 2;
            for(int ii = i+1; ii <= m; ii++) {
                fx[i] += row[ii] * now * now;
                now += 4;
            }
        }
        
        FOR(j,0,n) {
            ll now = 2;
            for(int jj = j; jj >= 1; jj--) {
                fy[j] += col[jj] * now * now;
                now += 4;
            }
            now = 2;
            for(int jj = j+1; jj <= n; jj++) {
                fy[j] += col[jj] * now * now;
                now += 4;
            }
        }
        
        long long res = 1000111000111000111LL;
        int savei, savej;
        FOR(i,0,m) FOR(j,0,n)
        if (fx[i] + fy[j] < res) {
            res = min(res, fx[i] + fy[j]);
            savei = i; savej = j;
        }
        cout << res << endl;
        cout << savei << ' ' << savej << endl;
    }
    return 0;
}
