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

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    double len() { return sqrt(x*x + y*y); }
} a[2011];

double f[1011][1011], x[1011];

bool operator < (const Point &a, const Point &b) {
    return a.x < b.x;
}

int n;
double L, W;

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        cin >> L >> W;
        FOR(i,1,n) {
            cin >> a[i].x;
            a[i].y = 0;
        }
        sort(a+1, a+n+1);

        double each = L / ((n/2)-1.0), cur = 0.0, res = 0.0;
        FOR(i,1,n/2) x[i] = (i-1) * each;

        FOR(i,0,n/2) FOR(j,0,n/2) f[i][j] = 1e20;

        f[0][0] = 0;
        FOR(i,0,n/2) FOR(j,0,n/2) if (i < n/2 || j < n/2) {
            int next = i + j + 1;
            f[i+1][j] = min(f[i+1][j], f[i][j] + (a[next] - Point(x[i+1], 0)).len());
            f[i][j+1] = min(f[i][j+1], f[i][j] + (a[next] - Point(x[j+1], W)).len());
        }

        cout << f[n/2][n/2] << endl;
    }
    return 0;
}
