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
const int MN = 100111;

int n, x[MN];
long long f[4][MN];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        n--;
        FOR(i,1,n) scanf("%d", &x[i]);
        
        memset(f, 0, sizeof f);
        FORD(i,n,1) {
            f[0][i] = (x[i]-1) / 2 * 2 + 1 + max(f[0][i+1], f[1][i+1]);
            if (x[i] < 2) f[1][i] = 0;
            else f[1][i] = x[i] / 2 * 2 + f[1][i+1];
        }
        
        FOR(i,2,n+1) {
            f[2][i] = (x[i-1]-1) / 2 * 2 + 1 + max(f[2][i-1], f[3][i-1]);
            if (x[i-1] < 2) f[3][i] = 0;
            else f[3][i] = x[i-1] / 2 * 2 + f[3][i-1];
        }
        
//        REP(t,4) {
//            FOR(i,1,n+1) cout << f[t][i] << ' ';
//            cout << endl;
//        }
        
        long long res = 0;
        FOR(i,1,n+1) {
            res = max(res, f[0][i]);
            res = max(res, f[2][i]);
            res = max(res, f[1][i] + f[2][i]);
            res = max(res, f[3][i] + f[0][i]);
        }
        cout << res << endl;
    }
    return 0;
}
