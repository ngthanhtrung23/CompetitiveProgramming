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

const long double PI = acos(-1.0);
struct Circle {
    long double x, y, r;
    Circle(long double x = 0, long double y = 0, long double r = 0) : x(x), y(y), r(r) {}
    void read() { cin >> x >> y >> r; }

    long double area() { return acos(-1.0) * r * r; }
    long double len() { return sqrt(x*x + y*y); }
    
    Circle operator - (Circle a) { return Circle(x-a.x, y-a.y, 0); }
} A, B;

long double commonCircleArea(Circle c1, Circle c2) { //return the common area of two circle
    long double d = hypot(c1.x-c2.x, c1.y-c2.y), area;
    if (c1.r+c2.r <= d) area = 0;
    else if (c2.r+d <= c1.r) area = (c1.r * c1.r - c2.r * c2.r) * PI;
    else if (c1.r+d <= c2.r) area = (c2.r * c2.r - c1.r * c1.r) * PI;
    else {
        long double p1 = c2.r * c2.r * acos((d*d + c2.r*c2.r - c1.r*c1.r) / (2*d*c2.r));
        long double p2 = c1.r * c1.r * acos((d*d + c1.r*c1.r - c2.r*c2.r) / (2*d*c1.r));
        long double p3 = 0.5 * sqrt((-d+c2.r+c1.r) * (d+c2.r-c1.r) * (d+c1.r-c2.r) * (d+c1.r+c2.r));
        area = p1 + p2 - p3;
    }
    return area;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(12);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        A.read(); B.read();
        double res = 0.0;
        if ((A - B).len() >= A.r + B.r) res = A.area();
        else if ((A - B).len() + B.r <= A.r) res = A.area() - B.area();
        else if ((A - B).len() + A.r <= B.r) res = 0.0;
        else {
            res = max((long double) 0.0, A.area() - commonCircleArea(A, B));
        }
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}
