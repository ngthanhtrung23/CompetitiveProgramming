
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

int v1, v2, t, d, v[111];

int main() {
    while (cin >> v1 >> v2) {
        cin >> t >> d;
        v[1] = v1;
        v[t] = v2;

        FOR(i,2,t-1) {
            v[i] = min(v1 + (i-1)*d, v2 + (t-i)*d);
        }
        int res = 0;
        FOR(i,1,t) res += v[i];
        cout << res << endl;
    }
    return 0;
}
