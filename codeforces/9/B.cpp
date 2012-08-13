#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

struct Point {
    long double x, y;
    Point() { x = y = 0; }
    Point(long double x, long double y = 0) : x(x), y(y) {}
    void read() { cin >> x >> y; }

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    long double sqlen() { return x*x + y*y; }
    long double len() { return sqrt(sqlen()); }
} a[111], U;

long double vs, vb;
int n;

long double ab(long double x) {
    if (x < 0) return -x;
    else return x;
}

int main() {
    while (cin >> n >> vb >> vs) {
        long double t;
        --n; cin >> t;
        FOR(i,1,n) {
            cin >> t;
            a[i] = Point(t, 0);
        }
        U.read();

        long double res = 1e100, res2 = 1e100;
        int save = -1;

        FOR(i,1,n) {
            long double now = (a[i] - Point(0,0)).len() / vb + (a[i] - U).len() / vs;
            long double now2 = (a[i] - U).len();
            if (now < res || ab(now - res) < 1e-6 && now2 < res2) {
                res = now;
                res2 = now2;
                save = i+1;
            }
        }
        cout << save << endl;
    }
    return 0;
}
