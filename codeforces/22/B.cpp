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

int m, n, s[33][33];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) {
            char c; cin >> c;
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1];
            if (c == '1') s[i][j]++;
        }

        int res = 0;
        FOR(i1,1,m) FOR(i2,i1,m) FOR(j1,1,n) FOR(j2,j1,n) {
            if (s[i2][j2] - s[i1-1][j2] - s[i2][j1-1] + s[i1-1][j1-1] == 0) {
                res = max(res, (i2 - i1 + 1) + (j2 - j1 + 1));
            }
        }
        cout << res*2 << endl;
    }
    return 0;
}

