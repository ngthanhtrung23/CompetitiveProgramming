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
    cout << (fixed) << setprecision(9);
    long long x1, y1, x2, y2, a, b, c;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        int n, res = 0;
        cin >> n;
        while (n--) {
            cin >> a >> b >> c;
            long long f1 = a*x1 + b*y1 + c;
            long long f2 = a*x2 + b*y2 + c;
            if (f1 < 0 && f2 > 0) ++res;
            if (f1 > 0 && f2 < 0) ++res;
        }
        cout << res << endl;
    }
    return 0;
}
