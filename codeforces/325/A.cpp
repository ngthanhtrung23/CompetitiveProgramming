
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
    int n;
    while (cin >> n) {
        long long sum = 0, x1, x2, y1, y2, minx, maxx, miny, maxy;
        minx = miny = 100111;
        maxx = maxy = -1;

        FOR(i,1,n) {
            cin >> x1 >> y1 >> x2 >> y2;
            minx = min(minx, x1);
            maxx = max(maxx, x2);
            miny = min(miny, y1);
            maxy = max(maxy, y2);

            sum += (x2 - x1) * (y2 - y1);
        }

        if (maxx - minx == maxy - miny && sum == (maxx - minx) * (maxy - miny)) cout << "YES"; else cout << "NO";
        cout << endl;
    }
    return 0;
}
