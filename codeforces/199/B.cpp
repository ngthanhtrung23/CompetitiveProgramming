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

struct Point {
    long long x, y;
    Point() { x = y = 0; }
    Point(long long x, long long y) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    long long sqlen() { return x*x + y*y; }
    long double len() { return sqrt(sqlen()); }

    void read() { cin >> x >> y; }
} A, B;

long long r1, r2, R1, R2;

bool inside(Point A, long long r1, Point B, long long r2) {
    return r2 + 1e-9 > (B-A).len() + r1;
}

bool cut(Point A, long long r1, Point B, long long r2) {
    if (inside(A, r1, B, r2)) return false;
    if (inside(B, r2, A, r1)) return false;
    return (A-B).len() < r1 + r2 - 1e-9;
}

bool check(Point A, long long r, Point B, long long r2, long long R2) {
    if (cut(A, r, B, r2)) return false;
    if (cut(A, r, B, R2)) return false;
    if (inside(A, r, B, R2)) {
        if (inside(B, r2, A, r)) return false;
        if (!cut(A, r, B, r2) && !inside(A, r, B, r2) && !inside(B, r2, A, r)) return false;
    }
    return true;
}

int main() {
    A.read(); cin >> r1 >> R1;
    B.read(); cin >> r2 >> R2;

    int res = 0;
    if (check(A, r1, B, r2, R2)) ++res;
    if (check(A, R1, B, r2, R2)) ++res;
    if (check(B, r2, A, r1, R1)) ++res;
    if (check(B, R2, A, r1, R1)) ++res;
    cout << res << endl;
    return 0;
}
