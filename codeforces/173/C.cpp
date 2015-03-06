//#pragma comment(linker, "/STACK:66777216")
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

int m, n, a[511][511], s[511][511], f[2][511][511];

int getSum(int i, int j, int u, int v) {
    if (i > u) swap(i, u);
    if (j > v) swap(j, v);
    return s[u][v] - s[i-1][v] - s[u][j-1] + s[i-1][j-1];
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &m, &n) == 2) {
        FOR(i,1,m) FOR(j,1,n) {
            scanf("%d", &a[i][j]);
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
        }
        int K = min(m, n);
        int cur = 1, res = -1000111000;
        for(int k = 3; k <= K; k += 2) {
            cur = 1 - cur;
            if (k == 3) {
                FOR(i,1,m-k+1) FOR(j,1,n-k+1) {
                    f[0][i][j] = a[i][j] + a[i][j+1] + a[i][j+2] + a[i+1][j+2]
                            + a[i+2][j] + a[i+2][j+1] + a[i+2][j+2];
                    res = max(res, f[0][i][j]);
                }
            }
            else {
                FOR(i,1,m-k+1) FOR(j,1,n-k+1) {
                    f[cur][i][j] = getSum(i,j,i+k-1,j+k-1) - a[i+1][j] - f[1-cur][i+1][j+1];
                    res = max(res, f[cur][i][j]);
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

