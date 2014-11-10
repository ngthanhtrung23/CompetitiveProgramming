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

const long long MOD = 1000000007LL;
int n, a[1011];
long long f[1011][20111];

void update(long long &x, long long val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        memset(f, 0, sizeof f);
        f[0][10000] = 1;
        long long res = 0;
        REP(i,n) {
            FOR(sum,0,20000)
                if (f[i][sum]) {
                    update(f[i+1][sum + a[i+1]], f[i][sum]);
                    update(f[i+1][sum - a[i+1]], f[i][sum]);
                }
            update(res, f[i+1][10000]);
            update(f[i+1][10000], 1);
        }
        cout << res << endl;
    }
    return 0;
}
