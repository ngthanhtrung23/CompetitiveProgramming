#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define SZ(x) ((int)(x).size())

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

struct P {
    int x, y, z;

    P() {}
    P(int x, int y, int z) : x(x), y(y), z(z) {}
};

bool operator < (const P& a, const P& b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}
istream& operator >> (istream& cin, P& p) {
    cin >> p.x >> p.y >> p.z;
    return cin;
}

int X, Y, Z;
struct R {
    P small, big;

    R() {}
    R(P p) : small(p), big(p) {}

    int volume() {
        return (big.x - small.x + 1)
            * (big.y - small.y + 1)
            * (big.z - small.z + 1);
    }

    bool isValid() {
        return 1 <= small.x && small.x <= big.x && big.x <= X
            && 1 <= small.y && small.y <= big.y && big.y <= Y
            && 1 <= small.z && small.z <= big.z && big.z <= Z;
    }
};
istream& operator >> (istream& cin, R& r) {
    cin >> r.small >> r.big;
    return cin;
}

int intersect_length(int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    return min(v, r) - max(l, u) + 1;
}

int intersect_volume(const R& a, const R& b) {
    return intersect_length(a.small.x, a.big.x, b.small.x, b.big.x)
        * intersect_length(a.small.y, a.big.y, b.small.y, b.big.y)
        * intersect_length(a.small.z, a.big.z, b.small.z, b.big.z);
}

bool check(const vector<R>& rects, const vector<P>& points) {
    for (auto r : rects) {
        if (!r.isValid()) return false;
    }

    REP(i, SZ(rects)) FOR(j,i+1,SZ(rects)-1) {
        if (intersect_volume(rects[i], rects[j]) > 0) return false;
    }

    REP(i, SZ(rects)) {
        if (intersect_volume(rects[i], R(points[i])) == 0) return false;
    }

    int total = 0;
    for (auto r : rects) total += r.volume();
    return total == X * Y * Z;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int nPoint;
    while (cin >> X >> Y >> Z >> nPoint && X > 0) {
        vector<P> points(nPoint);
        REP(i,nPoint) {
            cin >> points[i];
        }
        vector<R> rects(nPoint);
        for (auto& r : rects) {
            cin >> r;
        }

        cout << (check(rects, points) ? "YES" : "NO") << endl;
    }
    return 0;
}
