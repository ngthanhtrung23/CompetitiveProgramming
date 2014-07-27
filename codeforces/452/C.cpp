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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

long double f[1011][1011];
int m, n;

void init() {
    memset(f, 0, sizeof f);
    f[1][1] = 1;
    FOR(i,1,n-1) {
        FOR(x,0,min(i,m)) if (f[i][x] > 1e-50) {
            f[i+1][x] += f[i][x] * ((m*n-m) - (i-x)) / (double) (m*n - i);
            f[i+1][x+1] += f[i][x] * (m-x) / (double) (m*n-i);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(8);
    while (cin >> n >> m) {
        init();
        double res = 0.0;
        FOR(k,1,min(m,n)) {
            res += f[n][k] * k / (double) n;
        }
        cout << res << endl;
    }
    return 0;
}
