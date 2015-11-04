
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

int main() {
    ios :: sync_with_stdio(false);
    int n;
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) a[i].read();
        Point sum = Point(0, 0, 0);
        FOR(i,1,n) sum = sum + a[i];
        sum = sum / n;
//        sum.print();
        double rate = 20000;
        REP(turn,10000) {
            Point largest = Point(0, 0, 0);
            FOR(i,1,n) {
                Point cur = a[i] - sum;
                if (cur.len() > largest.len()) largest = cur;
            }
            if (largest.len() > rate) {
                largest = largest * (rate / largest.len());
            }
            sum = sum + largest;
            rate *= 0.997;
        }
        sum.print();
    }
}
