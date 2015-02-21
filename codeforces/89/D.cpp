
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
using namespace std;

struct Point {
    ll x, y, z;
    Point() {}
    Point(ll x, ll y, ll z) : x(x), y(y), z(z) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y, z+a.z); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y, z-a.z); }
    ll operator * (const Point& a) const { return x*a.x + y*a.y + z*a.z; }
    ll norm() { return x*x + y*y + z*z; }

    void read() { cin >> x >> y >> z; }
} A, v, O[111];
vector<Point> p[111], P[111];
int n;
ll r[111];

double res;
void update(Point O, ll r) {
    Point coeff = A - O;
    ll c = coeff.norm() - r * r;
    ll b = -2LL * (coeff * v);
    ll a = v.norm();

    ll delta = b*b - 4*a*c;
    if (delta < 0) return ;

    double x1 = -(-b - sqrt(delta)) / 2.0 / a;
    double x2 = -(-b + sqrt(delta)) / 2.0 / a;


    if (x1 >= 0) { if (res < 0) res = x1; else res = min(res, x1); }
    if (x2 >= 0) { if (res < 0) res = x2; else res = min(res, x2); }
}

int main() {
    ll R;
    A.read(); v.read(); cin >> R;
    cin >> n;
    FOR(i,1,n) {
        O[i].read(); cin >> r[i];
        int k; cin >> k;
        p[i].resize(k); P[i].resize(k);
        REP(j,k) {
            p[i][j].read();
            P[i][j] = p[i][j] + O[i];
        }
    }
    res = -1;
    FOR(i,1,n) {
        update(O[i], r[i] + R);
        for(auto Q : P[i]) {
            update(Q, R);
        }
    }

    if (res < 0) cout << -1 << endl;
    else cout << (fixed) << setprecision(14) << res << endl;
    return 0;
}
