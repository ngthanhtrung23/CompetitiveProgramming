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

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    long long n, a, b;
    while (cin >> n >> a >> b) {
        n *= 6;
        if (a * b >= n) {
            cout << a*b << endl << a << ' ' << b << endl;
            continue;
        }
        long long best = 1000111000111000LL, savex = -1, savey = -1;
        for(long long x = a; x*x <= n; ++x) {
            long long y = n / x;
            if (x * y < n) ++y;
            if (y < b) y = b;

            long long cur = x * y;
            if (cur < best) {
                best = cur;
                savex = x;
                savey = y;
            }
        }

        for(long long y = b; y*y <= n; ++y) {
            long long x = n / y;
            if (x * y < n) ++x;
            if (x < a) x = a;

            long long cur = x * y;
            if (cur < best) {
                best = cur;
                savex = x;
                savey = y;
            }
        }

        cout << best << endl << savex << ' ' << savey << endl;
    }
    return 0;
}
