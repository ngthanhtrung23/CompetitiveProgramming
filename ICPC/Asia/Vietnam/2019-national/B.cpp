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
    int id;

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
ostream& operator << (ostream& cout, const P& p) {
    cout << p.x << ' ' << p.y << ' ' << p.z;
    return cout;
}

int X, Y, Z;
pair<P, P> res[1011];

void processSameXY(int l, int r, int fromX, int toX, int fromY, int toY, const vector<P>& points) {
    int firstZ = 1;
    FOR(i,l,r) {
        int lastZ = (i == r) ? Z : points[i].z;

        res[points[i].id] = make_pair(
                P(fromX, fromY, firstZ),
                P(toX, toY, lastZ));
        firstZ = points[i].z + 1;
    }
}

void processSameX(int l, int r, int fromX, int toX, const vector<P>& points) {
    int firstY = 1;
    int i = l;
    while (i <= r) {
        int j = i;
        while (j + 1 <= r && points[j+1].y == points[i].y) {
            ++j;
        }

        processSameXY(i, j, fromX, toX, firstY, (j == r) ? Y : points[j].y, points);
        firstY = points[j].y + 1;
        i = j + 1;
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int nPoint;
    while (cin >> X >> Y >> Z >> nPoint && X > 0) {
        vector<P> points(nPoint);
        REP(i,nPoint) {
            cin >> points[i];
            points[i].id = i + 1;
        }
        sort(points.begin(), points.end());

        int firstX = 1;
        int i = 0;
        while (i < SZ(points)) {
            int j = i;
            while (j + 1 < SZ(points) && points[j+1].x == points[i].x) {
                ++j;
            }

            processSameX(i, j, firstX, (j+1 == SZ(points)) ? X : points[j].x, points);
            firstX = points[j].x + 1;
            i = j + 1;
        }

        cout << "YES" << '\n';
        FOR(i,1,nPoint) {
            cout << res[i].first << ' ' << res[i].second << '\n';
        }
    }
    return 0;
}
