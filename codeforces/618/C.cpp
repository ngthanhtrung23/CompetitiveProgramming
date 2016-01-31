
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

struct Point {
    ll x, y;
    int id;

    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }

    ll sqlen() { return x*x + y*y; }
} a[100111];

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    ll t = b.x * c.y - b.y * c.x;
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}
int n;

bool cmp(const Point& u, const Point& v) {
    int t = ccw(a[1], u, v);
    if (t == 0) return (u - a[1]).sqlen() < (v - a[1]).sqlen();
    return t < 0;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            a[i].id = i;
        }
        FOR(i,2,n) if (a[i].y < a[1].y || (a[i].y == a[1].y && a[i].x < a[1].x)) {
            swap(a[i], a[1]);
        }
        sort(a+2, a+n+1, cmp);
        int z = 3; while (ccw(a[1], a[2], a[z]) == 0) ++z;
        cout << a[1].id << ' ' << a[2].id << ' ' << a[z].id << endl;
    }
}
