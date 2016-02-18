
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

#define EPS 1e-6
const double PI = acos(-1.0);

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (double k) { return Point(x*k, y*k); }
    Point operator / (double k) { return Point(x/k, y/k); }

    double operator * (Point a) { return x*a.x + y*a.y; } // dot product
    double operator % (Point a) { return x*a.y - y*a.x; } // cross product

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    Point conj() { return Point(x, -y); }
    double norm() { return x*x + y*y; }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return sqrt(norm()); }

    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}

const int MN = 1511;
int n;
Point a[MN];

double x[MN * 2];

ll C3(ll n) {
    return n * (n - 1LL) * (n-2LL) / 6LL;
}
ll C4(ll n) {
    return n * (n-1LL) * (n-2LL) * (n-3LL) / 24LL;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        ll xx = 0;
        FOR(i,1,n) {
            ll sum = 0;
            int k = 0;

            FOR(j,1,n) if (j != i) {
                x[++k] = atan2(a[j].y - a[i].y, a[j].x - a[i].x);
            }
            assert(k == n-1);
            sort(x+1, x+n);

            FOR(i,k+1,k+k) x[i] = x[i-k] + 2*PI;

            int jj = 1;
            FOR(j,1,k) {
                while (x[jj+1] < x[j] + PI) ++jj;
                ll left = jj - j;
                ll right = k - left - 1;

                sum += left * right;
            }

//            PR(x, k+k);
//            DEBUG(sum);
//            DEBUG(a[i]);

            ll cur = (sum - C3(n-1)) / 2;
            xx += cur;
        }

        double res = ((C4(n) - xx) * 2 + xx) / (double) C3(n);
        cout << (fixed) << setprecision(9) << res << endl;
    }
}
