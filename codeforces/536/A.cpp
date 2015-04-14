
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

long long A, B, n, l, t, m, a[1000111], s[1000111];

bool check(long long r) {
    if (a[r] > t) return false;
    return s[r] - s[l-1] <= t*m;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> A >> B >> n) {
        FOR(i,1,1000*1000) {
            a[i] = A + (i-1) * B;
            s[i] = s[i-1] + a[i];
        }
        while (n--) {
            cin >> l >> t >> m;
            long long left = l, right = 1000000LL, res = l - 1;
            while (left <= right) {
                long long mid = (left + right) >> 1;
                if (check(mid)) {
                    res = mid;
                    left = mid + 1;
                }
                else right = mid - 1;
            }
            if (res < l) cout << -1 << '\n';
            else cout << res << '\n';
        }
    }
    return 0;
}
