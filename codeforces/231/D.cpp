
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

int a[11];

int main() {
    double x, y, z, x1, y1, z1;
    while (cin >> x >> y >> z >> x1 >> y1 >> z1) {
        FOR(i,1,6) cin >> a[i];
        int res = 0;
        if (x < 0) res += a[5];
        if (x > x1) res += a[6];
        if (y < 0) res += a[1];
        if (y > y1) res += a[2];
        if (z < 0) res += a[3];
        if (z > z1) res += a[4];
        cout << res << endl;
    }
    return 0;
}
