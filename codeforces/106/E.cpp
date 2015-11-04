
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 111;

struct Point {
    double x, y, z;

    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y, z-a.z);
    }
    Point operator + (const Point& a) const {
        return Point(x+a.x, y+a.y, z+a.z);
    }
    Point operator * (const double& k) const {
        return Point(x*k, y*k, z*k);
    }
    Point operator / (const double& k) const {
        return Point(x/k, y/k, z/k);
    }

    double len() {
        return sqrt(x*x + y*y + z*z);
    }

    void read() {
        cin >> x >> y >> z;
    }

    void print() {
        cout << x << ' ' << y << ' ' << z << endl;
    }
} a[MN];
int n;

double f(Point p) {
    double res = 0.0;
    FOR(i,1,n) res = max(res, (p - a[i]).len());
    return res;
}

pair<double, double> get_z(double x, double y) {
    double l = -1e4, r = 1e4;
    REP(turn,60) {
        double z1 = (l + l + r) / 3.0;
        double z2 = (l + r + r) / 3.0;

        double f1 = f(Point(x, y, z1));
        double f2 = f(Point(x, y, z2));

        if (f1 < f2) r = z2;
        else l = z1;
    }
    double z = (l + r) / 2.0;
    return make_pair(f(Point(x, y, z)), z);
}

pair<double, double> get_y(double x) {
    double l = -1e4, r = 1e4;
    REP(turn,60) {
        double y1 = (l + l + r) / 3.0;
        double y2 = (l + r + r) / 3.0;

        pair<double,double> f1 = get_z(x, y1);
        pair<double,double> f2 = get_z(x, y2);

        if (f1 < f2) r = y2;
        else l = y1;
    }
    double y = (l + r) / 2.0;
    pair<double,double> f = get_z(x, y);

    return make_pair(f.first, y);
}

pair<double,double> get_x() {
    double l = -1e4, r = 1e4;
    REP(turn,60) {
        double x1 = (l + l + r) / 3.0;
        double x2 = (l + r + r) / 3.0;
        
        pair<double,double> f1 = get_y(x1);
        pair<double,double> f2 = get_y(x2);

        if (f1 < f2) r = x2;
        else l = x1;
    }
    double x = (l + r) / 2.0;
    pair<double,double> f = get_y(x);

    return make_pair(f.first, x);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) a[i].read();
        pair<double,double> t = get_x();
        double x = t.second;
        t = get_y(x);
        double y = t.second;
        t = get_z(x, y);
        double z = t.second;

        cout << x << ' ' << y << ' ' << z << endl;
    }
}
