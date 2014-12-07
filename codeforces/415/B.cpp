#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n;
    long long a, b;
    while (cin >> n >> a >> b) {
        FOR(i,1,n) {
            long long x; cin >> x;
            long long has = x * a / b;

            long long l = 0, r = x, res = x;
            while (l <= r) {
                long long mid = (l + r) >> 1;
                if ((mid * a) / b == has) {
                    res = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }
            cout << x - res << ' ';
        }
        cout << endl;
    }
    return 0;
}
