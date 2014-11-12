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

int n, t[2011], c[2011];
long long f[2011][4011];
const long long oo = 1000111000111000LL;

void update(long long &x, long long val) {
    x = min(x, val);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> t[i] >> c[i];

        FOR(i,0,n) FOR(j,0,4000) f[i][j] = oo;
        f[0][2000] = 0;
        FOR(i,0,n-1) FOR(j,0,4000) if (f[i][j] < oo) {
            update(f[i+1][j-1], f[i][j]);
            update(f[i+1][min(4000, j+t[i+1])], f[i][j] + c[i+1]);
        }
        long long res = oo;
        FOR(j,2000,4000) update(res, f[n][j]);
        cout << res << endl;
    }
    return 0;
}
