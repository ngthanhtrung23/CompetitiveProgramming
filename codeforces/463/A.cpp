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

int x[111], y[111];

int main() {
    ios :: sync_with_stdio(false);
    int n, s;
    while (cin >> n >> s) {
        int res = -1;
        s *= 100;
        FOR(i,1,n) {
            cin >> x[i] >> y[i];
            int cur = x[i] * 100 + y[i];

            if (cur <= s) {
                res = max(res, y[i] ? (100 - y[i]) : 0);
            }
        }
        cout << res << endl;
    }
    return 0;
}
