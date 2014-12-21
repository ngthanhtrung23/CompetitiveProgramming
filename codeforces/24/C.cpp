#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
#define ll long long

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
} a[100111];


int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(6);
    int n; ll j;
    while (cin >> n >> j) {
        j %= 2*n;
        Point M; cin >> M.x >> M.y;
        REP(i,n) cin >> a[i].x >> a[i].y;

        if (j == 0) {
            cout << M.x << ' ' << M.y << endl;
            continue;
        }

        FOR(x,1,j) {
            M = a[(x-1) % n] + a[(x-1) % n] - M;
            if (x == j) cout << M.x << ' ' << M.y << endl;
        }
    }
    return 0;
}
