
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

const double PI = acos(-1.0);
const double EPS = 1e-6;

bool rect_in_rect(double X, double Y, double x, double y) {
   if (Y > X) swap(Y, X);
   if (y > x) swap(y, x);
   double diagonal = sqrt(double(X)*X + double(Y)*Y);
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
    ios :: sync_with_stdio(false);
    double a1, b1, a2, b2;
    while (cin >> a1 >> b1 >> a2 >> b2) {
        if (rect_in_rect(a1 + EPS, b1 + EPS, a2, b2)
                || rect_in_rect(a2 + EPS, b2 + EPS, a1, b1)) {
            cout << "Yes";
        }
        else cout << "No";
        cout << endl;
    }
}

