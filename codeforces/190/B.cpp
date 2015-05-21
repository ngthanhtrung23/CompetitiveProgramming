
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

struct Circle {
    double x, y, r;
    istream& read() { return (cin >> x >> y >> r); }
} a, b;

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (a.read() && b.read()) {
        double d = sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
        if (d + a.r <= b.r) cout << (b.r - a.r - d) / 2.0 << endl;
        else if (d + b.r <= a.r) cout << (a.r - b.r - d) / 2.0 << endl;
        else if (d <= a.r + b.r) cout << 0 << endl;
        else cout << (d - a.r - b.r) / 2.0 << endl;
    }
    return 0;
}
