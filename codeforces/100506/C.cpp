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
    int test; scanf("%d", &test);
    while (test--) {
        int x1, x2; scanf("%d.%d", &x1, &x2);
        int x = x1 * 100 + x2;
        int n, g = -1;
        scanf("%d", &n);
        FOR(i,1,n) {
            int a; scanf("%d", &a);
            a *= 100;
            while (a % 2 == 0) a /= 2;

            if (g == -1) g = a;
            else g = __gcd(g, a);
        }

        if (x % g == 0) cout << "yes" << endl;
        else cout << "no" << endl;
    }
    return 0;
}
