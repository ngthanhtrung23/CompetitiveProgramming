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
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

struct Point {
    int x, y;
    int k;
    int norm() const { return x*x + y*y; }
    double len() { return sqrt(norm()); }

    void read() { cin >> x >> y >> k; }
} a[1011];

bool operator < (const Point &a, const Point &b) {
    return a.norm() < b.norm();
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(9);
    int n, s;
    while (cin >> n >> s) {
        FOR(i,1,n) a[i].read();
        sort(a+1, a+n+1);

        int cur = s;
        if (cur >= 1000000) {
            cout << 0 << endl;
            continue;
        }
        FOR(i,1,n) {
            cur += a[i].k;
            if (cur >= 1000000) {
                cout << a[i].len() << endl;
                break;
            }
        }
        if (cur < 1000000) {
            cout << -1 << endl;
        }
    }
    return 0;
}
