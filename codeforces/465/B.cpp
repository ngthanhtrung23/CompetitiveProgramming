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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n, a[1011], f[2][1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        while (n > 0 && a[n] == 0) --n;

        f[0][0] = 0;
        f[1][0] = 1000111000;

        FOR(i,1,n) {
            if (a[i] == 0) {
                f[0][i] = min(f[0][i-1], f[1][i-1] + 1);
                f[1][i] = min(f[1][i-1] + 1, f[0][i-1] + 1);
            }
            else {
                f[0][i] = min(f[0][i-1] + 2, f[1][i-1] + 2);
                f[1][i] = min(f[1][i-1] + 1, f[0][i-1] + 1);
            }
        }
        cout << min(f[0][n], f[1][n]) << endl;
    }
    return 0;
}
