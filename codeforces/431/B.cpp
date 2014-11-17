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

int a[7][7];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> a[1][1]) {
        FOR(i,1,5) FOR(j,1,5) if (i > 1 || j > 1) cin >> a[i][j];
        int res = 0;
        int x[7];
        FOR(i,1,5) x[i] = i;
        do {
            int cur = 0;
            // PR(x, 5);
            for(int i = 1; i <= 4; i += 1) {
                for(int j = i; j <= 4; j += 2) {
                    // cout << x[j] << ' ' << x[j+1] << endl;
                    cur += a[x[j]][x[j+1]] + a[x[j+1]][x[j]];
                }
            }
            res = max(res, cur);
        } while (next_permutation(x+1, x+6));
        cout << res << endl;
    }
    return 0;
}

