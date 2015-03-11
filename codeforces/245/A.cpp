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
    int good[3], bad[3];
    int n;
    while (cin >> n) {
        memset(good, 0, sizeof good);
        memset(bad, 0, sizeof bad);

        FOR(i,1,n) {
            int t, a, b; cin >> t >> a >> b;
            good[t] += a;
            bad[t] += b;
        }
        FOR(t,1,2) {
            if (good[t] >= bad[t]) cout << "LIVE"; else cout << "DEAD";
            cout << endl;
        }
    }
    return 0;
}

