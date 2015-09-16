
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
#define double long double
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(12);
    ll a, b;
    while (cin >> a >> b) {
        bool found = false;
        double res = -1;

        if (a < b) {
            cout << -1 << endl;
            continue;
        }

        if (a == b) {
            cout << b << endl;
            continue;
        }

        res = 1e50;

        ll k = (a - b) / (2 * b);
        if (k == 0) {
            cout << (a + b) / (double) (2*k+2) << endl;
            continue;
        }

        double x;
        x = (a - b) / (double) (2.0 * k);

        res = min(res, x);

        k = (a - b) / (2 * b);
        x = (a + b) / (double) (2.0 * k + 2);
        res = min(res, x);

        cout << res << endl;
    }
}
