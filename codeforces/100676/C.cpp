
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

int a[100111];

int main() {
    ios :: sync_with_stdio(false);
    int test; cin >> test;
    while (test--) {
        int k, m, n; cin >> k >> m >> n;
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1, greater<int>());

        int avail = k;
        FOR(i,1,n) avail -= a[i];

        FOR(i,0,n) {
            avail += a[i];
            if (avail >= m) {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}
