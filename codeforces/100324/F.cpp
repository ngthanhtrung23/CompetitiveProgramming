
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

struct Point {
    int x, y, z;

    Point() {}

    Point(int x, int y, int z) : x(x), y(y), z(z) {}

    void read() {
        cin >> x >> y >> z;
    }
};

bool operator < (const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

bool operator != (const Point& a, const Point& b) {
    return a.x != b.x
        || a.y != b.y
        || a.z != b.z;
}

struct Seg {
    Point X, Y;

    Seg() {}

    Seg(Point a, Point b) {
        X = a;
        Y = b;
        if (Y < X) swap(X, Y);
    }
};

bool operator < (const Seg& a, const Seg& b) {
    if (a.X != b.X) return a.X < b.X;
    return a.Y < b.Y;
}

int n;
set<Point> v;
set<Seg> e;

int main() {
    ios :: sync_with_stdio(false);
    freopen("genus.in", "r", stdin);
    freopen("genus.out","w", stdout);
    while (cin >> n) {
        v.clear(); e.clear();
        FOR(i,1,n) {
            Point a, b, c;
            a.read(); b.read(); c.read();

            v.insert(a);
            v.insert(b);
            v.insert(c);

            e.insert(Seg(a, b));
            e.insert(Seg(b, c));
            e.insert(Seg(c, a));
        }
//        DEBUG(SZ(v));
//        DEBUG(SZ(e));

        int x = SZ(v) - SZ(e) + n;
        cout << (2 - x) / 2 << endl;
    }
}
