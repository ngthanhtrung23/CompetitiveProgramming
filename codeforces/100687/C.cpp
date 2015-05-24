
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

int main() {
    ios :: sync_with_stdio(false);
    int n, m, x, y, z;
    while (cin >> n >> m >> x >> y >> z) {
        int can;
        can = min(x, m); x -= can; m -= can;
        can = min(y, m); y -= can; m -= can;
        can = min(z, m); z -= can; m -= can;

        if (m) {
            cout << "No" << endl;
            continue;
        }

        can = x + y*2 + z*3;
        cout << (can >= n ? "Yes" : "No") << endl;
    }
    return 0;
}

