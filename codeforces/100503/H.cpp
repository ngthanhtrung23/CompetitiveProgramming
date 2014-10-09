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
    ios :: sync_with_stdio(false); cin.tie(NULL);
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    double s, p;
    int m;
    while (cin >> s >> m >> p) {
        p /= 100.0;

        double l = 0, r = 1e9, res = r;
        REP(turn,1000) {
            double cur = s, mid = (l + r) / 2.0;
            FOR(i,1,m) {
                cur = cur * (1 + p);
                cur -= mid;
            }

            if (cur <= 0) res = mid, r = mid;
            else l = mid;
        }
        cout << (fixed) << setprecision(6) << res << endl;
    }
    return 0;
}
