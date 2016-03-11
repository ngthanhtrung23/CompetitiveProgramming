#include <bits/stdc++.h>
#define int long long
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

int readInt() {
    int x; scanf("%lld", &x);
    return x;
}
void writeInt(int x) {
    printf("%lld", x);
}

const int MN = 1000111;
struct Point {
    int x, y;
    int id;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    void read() {
        x = readInt();
        y = readInt();
    }

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    int operator * (const Point& a) const { return x*a.x + y*a.y; }
    int operator % (const Point& a) const { return x*a.y - y*a.x; }
} queries[MN], points[MN];

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    int t = b % c;
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

int nPoints, nQueries;
int res[MN];

int ADD = -1;
int QUERY = +1;

int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));
bool operator < (const Point& a, const Point& b) {
    int t = ccw(Point(0, 0), a, b);
    if (t == RE_TRAI) return true;
    if (t == RE_PHAI) return false;

    return false;
}

Point hull[MN];
int nHull;

#undef int
int main() {
#define int long long
    while (scanf("%lld", &nQueries) == 1) {
        FOR(i,1,nQueries) {
            queries[i].read();
            queries[i].id = i;
        }
        nPoints = readInt();
        FOR(i,1,nPoints) {
            points[i].read();
            points[i].id = i;
        }
        sort(queries+1, queries+nQueries+1);
        sort(points+1, points+nPoints+1);

        FOR(i,1,nQueries) res[i] = 2000111000111000111LL;

        nHull = 0;
        FOR(i,1,nPoints) {
            while (nHull >= 2 && ccw(hull[nHull-1], hull[nHull], points[i]) != RE_PHAI) --nHull;
            hull[++nHull] = points[i];
        }
        FOR(i,1,nQueries) {
            int x = queries[i].id;
            int l = 1, r = nHull - 1;
            res[x] = min(hull[1] * queries[i], hull[nHull] * queries[i]);

            while (l <= r) {
                int mid = (l + r) >> 1;
                int y1 = hull[mid] * queries[i];
                int y2 = hull[mid + 1] * queries[i];

                res[x] = min(res[x], min(y1, y2));
                if (y1 < y2) {
                    r = mid - 1;
                }
                else l = mid + 1;
            }
        }
        FOR(i,1,nQueries) {
            writeInt(res[i]);
            putchar(' ');
        }
        puts("");
    }
}
