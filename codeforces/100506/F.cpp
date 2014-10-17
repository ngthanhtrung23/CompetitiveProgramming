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

const int MN = 55;

double f[MN][MN], w, p, a[MN];
int n;

bool check() {
    multiset<double> pieces;
    FOR(i,1,n) pieces.insert(a[i]);
    while (pieces.size() > 1) {
        double a = *pieces.begin(); pieces.erase(pieces.begin());
        double b = *pieces.begin(); pieces.erase(pieces.begin());

        double x = (a + b) / (1 - p);
        pieces.insert(x);
    }
    return *pieces.begin() < w + 1e-9;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(9);
    int test; cin >> test;
    while (test--) {
        cin >> w >> p >> n;
        p /= 100.0;
        FOR(i,1,n) cin >> a[i];

        if (!check()) {
            cout << -1 << endl;
            continue;
        }

        double l = 0.0, r = w, res = 0.0;
        ++n;
        REP(turn,50) {
            double mid = (l + r) / 2.0;
            a[n] = mid;
            if (check()) {
                res = mid;
                l = mid;
            } else r = mid;
        }
        cout << res << endl;
    }
    return 0;
}
