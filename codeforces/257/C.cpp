
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

const int MN = 100111;

struct Point {
    double x, y;
    double f;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    friend istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y;
        return cin;
    }
    friend ostream& operator << (ostream& cout, Point& p) {
        cout << p.x << ' ' << p.y;
        return cout;
    }
} a[MN];

bool operator < (const Point& a, const Point& b) {
    return a.f < b.f;
}
int n;

const double PI = acos((double) -1.0);
double RAD_to_DEG(double r) { return r * 180.0 / PI; }
double directed_angle(Point a, Point o, Point b) { // angle AOB, in range [0, 2*PI)
    double t = -atan2(a.y - o.y, a.x - o.x)
            + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2*PI;
    return t;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        set< pair<int,int> > all;
        
        int nn = 0;
        FOR(i,1,n) {
            int x, y; cin >> x >> y;
            int g = __gcd(abs(x), abs(y));
            x /= g;
            y /= g;

            if (all.count(make_pair(x, y))) continue;
            all.insert(make_pair(x, y));

            ++nn;
            a[nn] = Point(x, y);
            a[nn].f = atan2(y, x);
        }
        n = nn;

        if (n == 1) {
            cout << 0.0 << endl;
            continue;
        }
        sort(a+1, a+n+1);
        a[0] = a[n];
        a[n+1] = a[1];

//        cout << "----" << endl;
//        FOR(i,1,n) cout << a[i] << endl;

        double res = 1e9;
        Point O(0, 0);
        FOR(i,1,n) {
            Point A = a[i];
            Point B = a[i-1];
            res = min(res, directed_angle(A, O, B));
        }
        cout << RAD_to_DEG(res) << endl;
    }
}
