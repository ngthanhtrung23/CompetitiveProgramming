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

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        if (n < 4) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        int cnt = 0;
        while (n > 5) {
            cout << n << " - " << n-1 << " = 1\n";
            n -= 2;

            ++cnt;
        }

        if (n == 4) {
            cout << "1 * 2 = 2\n";
            cout << "2 * 3 = 6\n";
            cout << "6 * 4 = 24\n";
        } else {
            cout << "5 * 4 = 20\n";
            cout << "3 - 1 = 2\n";
            cout << "2 * 2 = 4\n";
            cout << "20 + 4 = 24\n";
        }

        while (cnt--) {
            cout << "24 * 1 = 24\n";
        }
    }
    return 0;
}
