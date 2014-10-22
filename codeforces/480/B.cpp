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

int n, l, x, y, a[100111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> l >> x >> y) {
        set<int> s;
        bool hasX = false, hasY = false;

        FOR(i,1,n) {
            cin >> a[i];
            if (s.count(a[i] - x)) hasX = true;
            if (s.count(a[i] - y)) hasY = true;
            s.insert(a[i]);
        }
        if (hasX && hasY) cout << 0 << endl;
        else if (hasX) cout << 1 << endl << y << endl;
        else if (hasY) cout << 1 << endl << x << endl;
        else {
            bool can = false;
            FOR(i,1,n) {
                if (s.count(a[i] - x - y) && a[i] - x - y >= 0) {
                    can = true;
                    cout << 1 << endl << a[i] - x << endl;
                    break;
                }
            }
            if (can) continue;

            FOR(i,1,n) {
                if (s.count(a[i] - x + y) && a[i] - x >= 0) {
                    cout << 1 << endl << a[i] - x << endl;
                    can = true;
                    break;
                }
            }
            if (can) continue;

            FOR(i,1,n) {
                if (s.count(a[i] - y + x) && a[i] - y >= 0) {
                    cout << 1 << endl << a[i] - y << endl;
                    can = true;
                    break;
                }
            }
            if (can) continue;

            FOR(i,1,n) {
                if (s.count(a[i] + x - y) && a[i] + x <= l) {
                    cout << 1 << endl << a[i] + x << endl;
                    can = true;
                    break;
                }
            }
            if (can) continue;

            FOR(i,1,n) {
                if (s.count(a[i] + y - x) && a[i] + y <= l) {
                    cout << 1 << endl << a[i] + y << endl;
                    can = true;
                    break;
                }
            }
            if (can) continue;

            cout << 2 << endl << x << ' ' << y << endl;
        }
    }
    return 0;
}
