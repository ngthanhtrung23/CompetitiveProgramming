
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%d", &x); }

const int MN = 111;

struct Point {
    int x, y;

    Point() { x = y = 0; }
    Point(int x, int y) : x(x), y(y) {}

    void read() {
        GI(x); GI(y);
    }
} a[MN];

int cx[MN], cy[MN], sx, sy;
int n, R;

bool good(int i, int x, int y) {
    return a[i].x >= x && a[i].x <= x + R
        && a[i].y >= y && a[i].y <= y + R;
}

int good1[MN][MN][MN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; GI(ntest);
    FOR(test,1,ntest) {
        GI(n); GI(R);
        FOR(i,1,n) {
            a[i].read();
        }

        sx = sy = 0;
        FOR(i,1,n) {
            cx[++sx] = a[i].x;
            cx[++sx] = a[i].x - R;

            cy[++sy] = a[i].y;
            cy[++sy] = a[i].y - R;
        }
        sort(cx+1, cx+sx+1);
        sort(cy+1, cy+sy+1);

        sx = unique(cx+1, cx+sx+1) - cx - 1;
        sy = unique(cy+1, cy+sy+1) - cy - 1;
//        PR(cx, sx);
//        PR(cy, sy);

        int res = 0;
        FOR(i,1,n)
            FOR(i1,1,sx) FOR(j1,1,sy) {
                good1[i][i1][j1] = good(i, cx[i1], cy[j1]);
            }

        FOR(i1,1,sx) FOR(j1,1,sy) {
            FOR(i2,i1,sx) FOR(j2,1,sy) {
                int cnt = 0;
                FOR(i,1,n) {
                    if (good1[i][i1][j1] || good1[i][i2][j2]) ++cnt;
                }
                res = max(res, cnt);
            }
        }
        DEBUG(test);
        cout << "Case #" << test << ": " << res << endl;
    }
}
