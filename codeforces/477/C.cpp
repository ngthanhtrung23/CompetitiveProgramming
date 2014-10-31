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

const int oo = 1000111000;
string s, p;
int f[2011][2011], res[2011];

void update(int &x, int val) {
    x = min(x, val);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s >> p) {
        int ls = s.length(), lp = p.length();
        string initial_p = p;
        while (p.length() < ls) p += initial_p;
        // DEBUG(s);
        // DEBUG(p);

        FOR(i,0,ls) FOR(j,0,ls) f[i][j] = oo;
        f[0][0] = 0;

        FOR(i,0,ls-1) FOR(j,0,i) if (f[i][j] < oo) {
            if (s[i] == p[j]) {
                update(f[i+1][j+1], f[i][j]);
            }
            if (j % lp == 0) {
                update(f[i+1][j], f[i][j]);
            }
            update(f[i+1][j], f[i][j] + 1);
        }

        memset(res, 0, sizeof res);
        FOR(i,ls,ls) FOR(j,0,i) {
            if (j % lp == 0) {
                int nn = f[i][j];
                int ln = ls - j;

                FOR(x,nn,ln) res[x] = max(res[x], j / lp);
            }
        }
        FOR(i,0,ls) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
