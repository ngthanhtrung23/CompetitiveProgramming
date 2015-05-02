
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int n;
struct Rect {
    int x1, y1, x2, y2;
} a[1011];

long long sum1(long long x) {
    return x * (x+1) / 2;
}

long long sum2(long long x) {
    return x*(x+1)*(2*x+1) / 6;
}

long long get1(long long X, long long Y) {
    if (X < Y) swap(X, Y);

    // X >= Y
    return Y*(X*Y)
        - X * sum1(Y-1)
        - Y * sum1(Y-1)
        + sum2(Y-1);
}

long long get2(long long gap, long long h1, long long h2) {
    if (gap <= 0) return 0;

    return get1(gap, h1 + h2) - get1(gap, h1) - get1(gap, h2);
}

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> n && n) {
        FOR(i,1,n) {
            cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;

            if (a[i].x1 > a[i].x2) swap(a[i].x1, a[i].x2);
            if (a[i].y1 > a[i].y2) swap(a[i].y1, a[i].y2);
        }
        long long res = 0;
        FOR(i,1,n) {
            res += get1(a[i].x2 - a[i].x1, a[i].y2 - a[i].y1);
        }

        FOR(i,1,n) FOR(j,1,n) {
            if (a[i].y2 == a[j].y1) {
                int gap = min(a[i].x2, a[j].x2) - max(a[i].x1, a[j].x1) - 2;
                res += get2(gap, a[i].y2 - a[i].y1, a[j].y2 - a[j].y1);
            }
            if (a[i].x2 == a[j].x1) {
                int gap = min(a[i].y2, a[j].y2) - max(a[i].y1, a[j].y1) - 2;
                res += get2(gap, a[i].x2 - a[i].x1, a[j].x2 - a[j].x1);
            }
        }
        cout << "Case " << ++test << ": " << res << endl;
    }
    return 0;
}
