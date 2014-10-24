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
long long a, b, x, y;

bool check(long long n) {
    long long bad_a = n / x;
    long long bad_b = n / y;
    long long bad_both = n / x / y;

    long long can_a = n - bad_a;
    long long can_b = n - bad_b;
    long long can_both = n - bad_a - bad_b + bad_both;

    return can_a >= a && can_b >= b && can_a + can_b - can_both >= a + b;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> a >> b >> x >> y) {
        long long l = 0, r = 1000111000111LL, res = r;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}

