
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

int n, m, k, a[10111];

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        FOR(i,1,n) scanf("%d", &a[i]);
        if (n % 2 == 0) {
            puts("0");
            continue;
        }
        int x = a[1];
        for(int i = 1; i <= n; i += 2)
            x = min(x, a[i]);
        int each = (n + 1) / 2;
        long long minute = m / each;
        long long res = min((long long) x, k * minute);

        cout << res << endl;
    }
    return 0;
}
