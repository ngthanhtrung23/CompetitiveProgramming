
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

int n, a[5], b[5], c[5], d[5];

#define GO(i,u,v) if (u+v <= n) { cout << i << ' ' << u << ' ' << n - u << endl; can = true; break; }

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,4) cin >> a[i] >> b[i] >> c[i] >> d[i];

        bool can = false;
        FOR(i,1,4) {
            GO(i, a[i], c[i]);
            GO(i, a[i], d[i]);
            GO(i, b[i], c[i]);
            GO(i, b[i], d[i]);
        }
        if (!can) cout << -1 << endl;
    }
    return 0;
}
