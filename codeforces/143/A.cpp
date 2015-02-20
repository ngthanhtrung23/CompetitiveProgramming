
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

int r1, r2, c1, c2, d1, d2;

bool solve() {
    if ((r2 + c1 - d1) % 2) return false;
    int z = (r2 + c1 - d1) / 2;
    int x = c1 - z;
    int y = d2 - z;
    int t = r2 - z;

    if (x + y != r1) return false;
    if (z + t != r2) return false;

    if (x + z != c1) return false;
    if (y + t != c2) return false;

    if (x + t != d1) return false;
    if (y + z != d2) return false;

    if (x == y || x == z || x == t
            || y == z || y == t
            || z == t) return false;
    if (x < 1 || x > 9) return false;
    if (y < 1 || y > 9) return false;
    if (z < 1 || z > 9) return false;
    if (t < 1 || t > 9) return false;
    
    cout << x << ' ' << y << endl;
    cout << z << ' ' << t << endl;
    return true;
}

int main() {
    while (cin >> r1 >> r2 >> c1 >> c2 >> d1 >> d2) {
        if (!solve()) cout << -1 << endl;
    }
    return 0;
}
