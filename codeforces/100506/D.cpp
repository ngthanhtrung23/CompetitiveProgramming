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

int a[8011];
long long f[11][66];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int test; cin >> test;
    while (test--) {
        int m, n, q; cin >> m >> n >> q;
        FOR(i,1,m) {
            string s; cin >> s;
            a[i] = s.length();
        }

        memset(f, 0, sizeof f);
        f[0][0] = 1;
        FOR(i,0,n-1)
            FOR(l,0,50)
            if (f[i][l] >= 0) {
                FOR(add,1,m)
                    f[i+1][l + a[add]] += f[i][l];
            }

        while (q--) {
            int x; cin >> x;
            cout << f[n][x] << endl;
        }
    }
    return 0;
}
