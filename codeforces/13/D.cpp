
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

const int MN = 1011;

struct Point {
    int x, y;
    int color;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    int operator % (const Point& a) const { return x*a.y - y*a.x; }

    void read() { cin >> x >> y; }

    friend ostream& operator << (ostream& cout, Point& p) {
        cout << p.x << ' ' << p.y;
        return cout;
    }
} red[MN], blue[MN], cur[MN];
int nRed, nBlue, n;

bool operator > (const Point& a, const Point& b) {
    if (a.y > b.y) return true;
    if (a.y < b.y) return false;
    return a.x > b.x;
}

int ccw(const Point& a, const Point& b, const Point& c) {
    int t = (b - a) % (c - a);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));
int RED = 1;
int BLUE = 0;

Point origin;
bool cmp(const Point& a, const Point& b) {
    int t = ccw(origin, a, b);
    if (t == RE_TRAI) return true;
    return false;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> nRed >> nBlue) {
        FOR(i,1,nRed) red[i].read();
        FOR(i,1,nBlue) blue[i].read();

        int res = 0;
        FOR(i,1,nRed) {
            n = 0;
            FOR(j,1,nRed) if (red[j] > red[i]) {
                ++n;
                cur[n] = red[j];
                cur[n].color = RED;
            }
            FOR(j,1,nBlue) if (blue[j] > red[i]) {
                ++n;
                cur[n] = blue[j];
                cur[n].color = BLUE;
            }
            origin = red[i];
            sort(cur+1, cur+n+1, cmp);

            FOR(j,1,n) if (cur[j].color == RED) {
                bool hasBlue = 0;
                Point minBlue;

                FOR(k,j+1,n) {
                    if (cur[k].color == BLUE) {
                        if (!hasBlue) {
                            hasBlue = true;
                            minBlue = cur[k];
                        }
                        else {
                            if (ccw(cur[j], minBlue, cur[k]) == RE_TRAI) {
                                minBlue = cur[k];
                            }
                        }
                    }
                    else {
                        if (!hasBlue) ++res;
                        else {
                            if (ccw(cur[j], minBlue, cur[k]) == RE_TRAI) {
                                ++res;
                            }
                        }
                    }
                }
            }
        }
        cout << res << endl;
    }
}
