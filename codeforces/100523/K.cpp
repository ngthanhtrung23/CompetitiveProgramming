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

const int MN = 100111;

inline long long det(long long a, long long b, long long c, long long d) {
    return a * d - b * c;
}
struct Point {
    long long x, y, z;
    Point(long long x = 0, long long y = 0, long long z = 0) : x(x), y(y), z(z) {}

    void read() { cin >> x >> y >> z; }
    void print() { cout << x << ' ' << y << ' ' << z << endl; }

    Point operator - (Point a) { return Point(x-a.x, y-a.y, z-a.z); }

    Point operator %(const Point &op) const {
        return Point(det(y, z, op.y, op.z), -det(x, z, op.x, op.z), det(x, y,
                op.x, op.y));
    }
    bool isZero() { return (!x) && (!y) && (!z); }
} a[MN];
int n;

struct Space {
    long long a, b, c, d;
    Space(Point p0, Point p1, Point p2) {
        a = p0.y * (p1.z - p2.z) + p1.y * (p2.z - p0.z) + p2.y * (p0.z - p1.z);
        b = p0.z * (p1.x - p2.x) + p1.z * (p2.x - p0.x) + p2.z * (p0.x - p1.x);
        c = p0.x * (p1.y - p2.y) + p1.x * (p2.y - p0.y) + p2.x * (p0.y - p1.y);
        d = -p0.x * (p1.y * p2.z - p2.y * p1.z) - p1.x * (p2.y * p0.z - p0.y * p2.z) 
- p2.x * (p0.y * p1.z - p1.y * p0.z);
    }

    long long f(Point p) {
        return a*p.x + b*p.y + c*p.z + d;
    }
};

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) a[i].read();

        if (n <= 3) {
            cout << "TAK" << endl;
            continue;
        }

        FOR(i,3,n) {
            if (!((a[i] - a[1]) % (a[2] - a[1])).isZero()) {
                swap(a[i], a[3]);
                break;
            }
        }

        if (((a[2] - a[1]) % (a[3] - a[1])).isZero()) {
            cout << "TAK" << endl;
            continue;
        }
        
        bool ok = true;
        Space s(a[1], a[2], a[3]);
        FOR(i,1,n) if (s.f(a[i])) ok = false;

        if (ok) cout << "TAK"; else cout << "NIE";
        cout << endl;
    }
    return 0;
}
