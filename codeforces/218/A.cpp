
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

int n, k, a[211];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n+n+1) cin >> a[i];

        for(int i=2; i <= n+n; i += 2) {
            int can = a[i] - max(a[i+1], a[i-1]) - 1;
            if (can > 1) can = 1;
            if (can > k) can = k;
            k -= can;
            a[i] -= can;
        }
        if (k > 0) cout << -1 << endl;
        else {
            FOR(i,1,n+n+1) cout << a[i] << ' '; cout << endl;
        }
    }
    return 0;
}

