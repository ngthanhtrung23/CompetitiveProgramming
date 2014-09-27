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
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

int n;
long long m, a[MN], b[MN];

bool check(long long val) {
    long long can = 0;
    if (val == 1) return true;

    FOR(i,1,n) if (a[i] >= val) {
        can += (a[i] - val) / b[i] + 1;
    }
    return can >= m;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) cin >> b[i];

        long long l = 1, r = 1000111000LL; long long res = l;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (check(mid)) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        long long has = 0, sum = 0;
        ++res;
        FOR(i,1,n) if (a[i] >= res) {
            long long can = (a[i] - res) / b[i] + 1;
            can = min(can, m - has);

            sum += can * a[i] - (can - 1) * can / 2 * b[i];

            has += can;
        }
        sum += (m - has) * (res - 1);
        cout << sum << endl;
    }
    return 0;
}

