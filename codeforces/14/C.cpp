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

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator == (Point a) { return x == a.x && y == a.y; }

    bool read() { return cin >> x >> y; }
} a[5], b[5];

void update(Point a, Point b, Point X, Point Y, bool &dir) {
    if (a == X && b == Y) dir = true;
    if (a == Y && b == X) dir = true;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    // freopen("input.txt", "r", stdin);

    while (a[1].read() && b[1].read()) {
        FOR(i,2,4) a[i].read(), b[i].read();

        int minx = a[1].x, miny = a[1].y;
        int maxx = a[1].x, maxy = a[1].y;

        FOR(i,1,4) {
            minx = min(minx, min(a[i].x, b[i].x));
            maxx = max(maxx, max(a[i].x, b[i].x));
            miny = min(miny, min(a[i].y, b[i].y));
            maxy = max(maxy, max(a[i].y, b[i].y));
        }

        if (minx == maxx || miny == maxy) {
            cout << "NO" << endl;
            continue;
        }

        bool left = false, right = false, up = false, down = false;
        Point A = Point(minx, miny);
        Point B = Point(maxx, miny);
        Point C = Point(maxx, maxy);
        Point D = Point(minx, maxy);

        FOR(i,1,4) {
            update(a[i], b[i], A, B, down);
            update(a[i], b[i], B, C, right);
            update(a[i], b[i], C, D, up);
            update(a[i], b[i], D, A, left);
        }

        if (left && right && up && down) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
}
