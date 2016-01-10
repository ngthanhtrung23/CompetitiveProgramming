
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

ll get(ll n) {
    ll l = 1, r = 1e9;
    ll res = 1e9;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (mid * (mid+1) * 3 >= n) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return res;
}

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator + (const Point& a) {
        return Point(x+a.x, y+a.y);
    }
    Point operator * (ll k) {
        return Point(x*k, y*k);
    }
};
Point v[11];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    ll n;
    v[1] = Point(1, 2);
    v[2] = Point(-1, 2);
    v[3] = Point(-2, 0);
    v[4] = Point(-1, -2);
    v[5] = Point(1, -2);
    v[6] = Point(2, 0);

    while (cin >> n) {
        if (n == 0) {
            cout << 0 << ' ' << 0 << endl;
            continue;
        }
        ll r = get(n);
//        DEBUG(r);

        ll last = 3 * r * (r + 1);
        ll s = last - 6*r;

        ll step;
        Point start, dir;

        if (n <= s + r) {
            step = n - (s + 1);
            start = v[2] + v[6] * r;
            dir = v[2];
        }
        else if (n <= s + 2*r) {
            step = n - (s + r + 1);
            start = v[3] + v[1] * r;
            dir = v[3];
        }
        else if (n <= s + 3*r) {
            step = n - (s + 2*r + 1);
            start = v[4] + v[2] * r;
            dir = v[4];
        }
        else if (n <= s + 4*r) {
            step = n - (s + 3*r + 1);
            start = v[5] + v[3] * r;
            dir = v[5];
        }
        else if (n <= s + 5*r) {
            step = n - (s + 4*r + 1);
            start = v[6] + v[4] * r;
            dir = v[6];
        }
        else {
            step = n - (s + 5*r + 1);
            start = v[1] + v[5] * r;
            dir = v[1];
        }
//        DEBUG(step);
        start = start + (dir * step);
        cout << start.x << ' ' << start.y << endl;
    }
}
