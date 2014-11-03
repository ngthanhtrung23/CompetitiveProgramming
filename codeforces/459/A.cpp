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
    int x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        if (x1 == x2) {
            int len = abs(y1 - y2);
            cout << x1 + len << ' ' << y1 << ' ' << x2 + len << ' ' << y2 << endl;
        }
        else if (y1 == y2) {
            int len = abs(x1 - x2);
            cout << x1 << ' ' << y1 + len << ' ' << x2 << ' ' << y2 + len << endl;
        }
        else {
            int l1 = abs(x1 - x2);
            int l2 = abs(y1 - y2);
            if (l1 != l2) cout << -1 << endl;
            else cout << x1 << ' ' << y2 << ' ' << x2 << ' ' << y1 << endl;
        }
    }
    return 0;
}
