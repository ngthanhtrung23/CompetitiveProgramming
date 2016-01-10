
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
#define double long double
using namespace std;

const double PI = acos((double) -1.0);
const double EPS = 1e-6;

bool rect_in_rect(double X, double Y, double x, double y) {
    X += EPS;
    Y += EPS;
    if (Y > X) swap(Y, X);
    if (y > x) swap(y, x);
    double diagonal = sqrt((double)(X)*X + (double)(Y)*Y);
    if (x < X && y < Y) return true;
    else if (y >= Y || x >= diagonal) return false;
    else {
        double w, theta, tMin = PI/4, tMax = PI/2;
        while (tMax - tMin > EPS) {
            theta = (tMax + tMin)/2.0;
            w = (Y-x*cos(theta))/sin(theta);
            if (w < 0 || x * sin(theta) + w * cos(theta) < X) tMin = theta;
            else tMax = theta;
        }
        return (w > y);
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("bricks.in", "r", stdin);
    freopen("bricks.out", "w", stdout);
    double a, b, c, d, e;
    while (cin >> a >> b >> c >> d >> e) {
        if (rect_in_rect(d, e, a, b)
                || rect_in_rect(d, e, b, c)
                || rect_in_rect(d, e, c, a)) {
            cout << "YES";
        }
        else cout << "NO";
        cout << endl;
    }
}
