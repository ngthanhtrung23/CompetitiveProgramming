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

int n, q, w[511], a[1011];
bool lifted[511];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> q) {
        FOR(i,1,n) cin >> w[i];
        FOR(i,1,q) cin >> a[i];

        int res = 0;
        FOR(i,1,q) {
            int last = 0;
            FOR(j,1,i-1) if (a[j] == a[i]) last = j;
            memset(lifted, false, sizeof lifted);

            FOR(x,last+1,i-1)
                if (!lifted[a[x]]) {
                    lifted[a[x]] = true;
                    res += w[a[x]];
                }
        }
        cout << res << endl;
    }
    return 0;
}
