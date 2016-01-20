
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

#define double long double
const double EPS = 1e-6;

int cmp(double a, double b) {
    if (fabs(a - b) < EPS) return 0;
    if (a < b) return -1;
    return 1;
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    double len() { return sqrt(x*x + y*y); }

    friend istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y;
        return cin;
    }
};

struct Circle : Point {
    double r;
} A1, A2, B1, B2;

bool inside(Circle a, Circle b) {  // b in a
    return cmp((a - b).len() + b.r, a.r) <= 0;
}

bool outside(Circle a, Circle b) {
    return cmp((a - b).len(), a.r + b.r) >= 0;
}

bool intersect(Circle a, Circle b) {
    if (a.r <= b.r) swap(a, b);  // now a is bigger circle

    // b inside a
    if (inside(a, b)) return false;

    // b outside a
    if (outside(a, b)) return false;
    return true;
}

bool in_middle(Circle a, Circle x, Circle y) {
    if (outside(a, x) && inside(y, a)) return true;
    if (inside(a, x) && inside(y, a)) return true;
    return false;
}

bool check(Circle a, Circle b1, Circle b2) {
    return !intersect(a, b1)
        && !intersect(a, b2)
        && !in_middle(a, b1, b2);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    double ra, RA, rb, RB;
    while (cin >> A1 >> ra >> RA >> B1 >> rb >> RB) {
        A2 = A1;
        B2 = B1;

        A1.r = ra;
        A2.r = RA;

        B1.r = rb;
        B2.r = RB;

        int res = 0;
        if (check(A1, B1, B2)) ++res;
        if (check(A2, B1, B2)) ++res;

        if (check(B1, A1, A2)) ++res;
        if (check(B2, A1, A2)) ++res;
        cout << res << endl;
    }
}
