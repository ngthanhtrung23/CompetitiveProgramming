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

int n, l, k, p[222], a[222];
long double f[222][422][222];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d", &n, &l, &k) == 3) {
        FOR(i,1,n) scanf("%d", &p[i]);
        FOR(i,1,n) scanf("%d", &a[i]);
        
        if (k > n) k = n;
        memset(f, 0, sizeof f);
        f[0][k+200][0] = 1.0;
        int space2;
        FOR(i,0,n-1) FOR(space,0,n+200) FOR(nWin,0,n) if (f[i][space][nWin] > 0) {
            // Win
            space2 = space + a[i+1];
            if (space2 > n + 200) space2 = n + 200;
            f[i+1][space2][nWin+1] += f[i][space][nWin] / 100.0 * p[i+1];
            
            // Lose
            f[i+1][space][nWin] += f[i][space][nWin] / 100.0 * (100 - p[i+1]);
        }
        long double res = 0.0;
        FOR(space,200,n+200) FOR(nWin,l,n)
            res += f[n][space][nWin];
        printf("%.8lf\n", (double) res);
    }
    return 0;
}
