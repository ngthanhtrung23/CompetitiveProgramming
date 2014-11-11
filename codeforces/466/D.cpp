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

const int MN = 2011;
const long long MOD = 1000000007;
int n, h, a[MN];
long long f[MN][MN];

void update(long long &x, long long val) {
    x = (x + val) % MOD;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> h) {
        FOR(i,1,n) {
            cin >> a[i];
            a[i] = h - a[i];
        }

        memset(f, 0, sizeof f);
        f[0][0] = 1;
        // f[i][x] = no ways to cover fully 1 --> i
        //           after i, there are still x opened intervals
        
        REP(i,n) FOR(x,0,i) if (f[i][x]) {
            // At i+1, we close 1 interval
            // There are x interval that we can choose
            if (x > 0 && x == a[i+1]) update(f[i+1][x-1], f[i][x] * x);
            
            // At i+1, we open 1 interval
            if (x + 1 == a[i+1]) update(f[i+1][x+1], f[i][x]);

            // At i+1, we close 1 interval, and then open a new one
            if (x + 1 == a[i+1]) update(f[i+1][x], f[i][x] * (x+1));

            // At i+1, we do nothing
            if (x == a[i+1]) update(f[i+1][x], f[i][x]);
        }

        cout << f[n][0] << endl;
    }
    return 0;
}
