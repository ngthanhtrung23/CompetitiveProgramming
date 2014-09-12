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

int n, k, f[10111][111], a[10111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) {
            cin >> a[i];
            a[i] %= k;
            if (a[i] < 0) a[i] += k;
        }

        memset(f, 0, sizeof f);
        f[1][a[1]] = true;

        FOR(i,1,n-1) REP(cur,k) if (f[i][cur]) {
            f[i+1][(cur + a[i+1]) % k] = true;
            f[i+1][(cur - a[i+1] + k) % k] = true;
        }

        cout << (f[n][0] ? "Divisible" : "Not divisible") << endl;
        break;
    }
    return 0;
}
