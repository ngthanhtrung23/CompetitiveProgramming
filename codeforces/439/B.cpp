#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

long long n, x, a[100111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> x) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);

        long long res = 0;
        FOR(i,1,n) {
            res += a[i] * x;
            --x; if (x == 0) ++x;
        }
        cout << res << endl;
    }
    return 0;
}
