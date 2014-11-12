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

string s;
bool f[5011][5011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        memset(f, false, sizeof f);
        int n = s.length();
        FOR(i,0,n-4)
            if (s.substr(i, 4) == "bear") {
                f[i][i+3] = true;
            }

        FORD(i,n-1,0) FOR(j,i,n-1)
            f[i][j] = f[i][j] || f[i+1][j] || f[i][j-1];

        int res = 0;
        REP(i,n) FOR(j,i+1,n-1)
            if (f[i][j]) ++res;

        cout << res << endl;
    }
    return 0;
}
