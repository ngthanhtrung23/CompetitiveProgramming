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

int n, m, col[511], c[511][511];
long long mod, f[2][511][511];

void update(long long &x, long long val) {
    x = (x + val) % mod;
}

void solve() {
    memset(f, 0, sizeof f);
    f[0][n-m][0] = 1;
    int cur = 0;

    FOR(j,1,n) {
        memset(f[1-cur], 0, sizeof f[1-cur]);
        FOR(zero,0,n-m) FOR(one,0,n-m) if (f[cur][zero][one]) {
            if (col[j] == 0) {
                update(f[1-cur][zero][one], f[cur][zero][one]);
            }
            else if (col[j] == 1) {
                // Not match
                if (zero > 0) update(f[1-cur][zero-1][one+1], f[cur][zero][one] * zero);
                // Match
                if (one > 0) update(f[1-cur][zero][one-1], f[cur][zero][one] * one);
            }
            else {
                // No match
                if (zero > 1) update(f[1-cur][zero-2][one+2], f[cur][zero][one] * c[zero][2]);
                // Match 1
                if (one > 0 && zero > 0) update(f[1-cur][zero-1][one], f[cur][zero][one] * zero % mod * one);
                // Match 2
                if (one > 1) update(f[1-cur][zero][one-2], f[cur][zero][one] * c[one][2]);
            }
        }
        cur = 1 - cur;
    }
    cout << f[cur][0][0] << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m >> mod) {
        FOR(i,0,500) {
            c[i][0] = 1;
            FOR(j,1,i) {
                c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
            }
        }
        FOR(j,1,n) col[j] = 2;
        FOR(i,1,m) FOR(j,1,n) {
            char c; cin >> c;
            if (c == '1') --col[j];
        }
        solve();
    }
    return 0;
}
