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

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

struct Point {
    long long x, y, z;

    Point() { x = y = z = 0; }
    Point(long long x, long long y, long long z) : x(x), y(y), z(z) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y, z-a.z); }
    long long operator * (Point a) { return x*a.x + y*a.y + z*a.z; }

    long long len() {
        return x*x + y*y + z*z;
    }
};

long long a[11][3];
bool found;

pair<long long, Point> others[11];

bool operator < (const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

bool check() {
    Point P = Point(a[0][0], a[0][1], a[0][2]);

    FOR(i,1,7) {
        Point cur = Point(a[i][0], a[i][1], a[i][2]);
        others[i] = make_pair((P - cur).len(), cur);
    }

    sort(others+1, others+8);
    if (others[1].first == 0) return false;

    if (others[1].first == others[2].first && others[1].first == others[3].first) {
        if (others[4].first == others[5].first && others[4].first == others[6].first) {
            if (others[1].first + others[2].first == others[4].first && others[1].first + others[4].first == others[7].first) {
                if ((others[1].second - P) * (others[2].second - P) == 0)
                if ((others[1].second - P) * (others[3].second - P) == 0)
                if ((others[2].second - P) * (others[3].second - P) == 0) {
                    Point Q = others[7].second;
                    if ((others[4].second - Q) * (others[5].second - Q) == 0)
                    if ((others[4].second - Q) * (others[6].second - Q) == 0)
                    if ((others[5].second - Q) * (others[6].second - Q) == 0) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void attempt(int i) {
    if (i == 8) {
        if (check()) {
            found = true;
            cout << "YES" << endl;
            REP(i,8) {
                REP(j,3)
                    cout << a[i][j] << ' ';
                cout << endl;
            }
        }
        return ;
    }
    do {
        attempt(i+1);
        if (found) return ;
    } while (next_permutation(a[i], a[i]+3));
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a[0][0]) {
        // DEBUG("hello");
        REP(i,8) {
            REP(dim,3) if (i || dim) cin >> a[i][dim];
            sort(a[i], a[i]+3);

            // PR0(a[i], 3);
        }

        found = false;
        attempt(1);
        if (!found) cout << "NO" << endl;
    }
    return 0;
}
