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

const int MOD = 1000000007;
int n, a, b, k;
int f[5011][5011];

void add(int &x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

void sub(int &x, int val) {
    x -= val;
    if (x < 0) x += MOD;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> a >> b >> k) {
        memset(f, 0, sizeof f);
        f[0][a] = 1;

        FOR(i,0,k-1) {
            FOR(x,1,n) {
                int d = abs(x - b) - 1;
                add(f[i+1][max(x - d, 1)], f[i][x]);
                sub(f[i+1][x], f[i][x]);
                add(f[i+1][x+1], f[i][x]);
                sub(f[i+1][min(x + d + 1, n + 1)], f[i][x]);
            }

            FOR(x,1,n) add(f[i+1][x], f[i+1][x-1]);
        }

        int res = 0;
        FOR(i,1,n) add(res, f[k][i]);
        cout << res << endl;
    }
    return 0;
}
