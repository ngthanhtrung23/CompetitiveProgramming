
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

int n, w, a[200111];

bool check(double val) {
    FOR(i,1,n) if (val > a[i]) return false;
    FOR(i,n+1,n+n) if (val*2 > a[i]) return false;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(10);
    while (cin >> n >> w) {
        FOR(i,1,2*n) cin >> a[i];
        sort(a+1, a+n+n+1);

        double l = 0.0, r = w / (3.0*n), res = 0;
        REP(turn,1000) {
            double mid = (l + r) / 2.0;
            if (check(mid)) res = mid, l = mid;
            else r = mid;
        }
        cout << res*(3*n) << endl;
    }
}
