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
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

string a[11];
char b[11][11];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> a[0]) {
        FOR(i,1,7) cin >> a[i];

        int res = 17;
        REP(mask,1<<16) {
            memset(b, 'W', sizeof b);

            REP(i,8) if (mask & (1<<i)) {
                REP(j,8) b[i][j] = 'B';
            }

            REP(j,8) if (mask & (1<<(j+8))) {
                REP(i,8) b[i][j] = 'B';
            }

            bool equal = true;
            REP(i,8) REP(j,8) if (a[i][j] != b[i][j]) equal = false;
            if (equal) res = min(res, __builtin_popcount(mask));
        }
        cout << res << endl;
    }
    return 0;
}
