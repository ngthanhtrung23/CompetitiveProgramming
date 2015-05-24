
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

int x[55];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            int a, b; cin >> a >> b;
            x[i] = a + b;
        }
        double avg = 0.0;
        FOR(i,1,n) avg += x[i];
        avg /= n;

        double res = 0.0;
        FOR(i,1,n) res += fabs(x[i] - avg);
        cout << (fixed) << setprecision(9) << res << endl;
    }
    return 0;
}

