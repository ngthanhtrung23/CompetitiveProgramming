
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

int n, d, l;
int res[111];

int main() {
    while (cin >> n >> d >> l) {
        FOR(i,1,n) res[i] = 1;

        FOR(i,1,n) {
            if (i % 2 == 1) --d;
            else ++d;
        }

        if (d > 0) {
            for(int i = 1; i <= n; i += 2) {
                int can = min(d, l - 1);
                res[i] += can;
                d -= can;
            }
        }
        else {
            d = -d;
            for(int i = 2; i <= n; i += 2) {
                int can = min(d, l - 1);
                res[i] += can;
                d -= can;
            }
        }
        if (d != 0) {
            cout << -1 << endl;
            continue;
        }

        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
