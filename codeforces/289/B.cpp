
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

int m, n, d, a[111*111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> d) {
        int t = 0;
        FOR(i,1,m) FOR(j,1,n) {
            ++t; cin >> a[t];
        }
        n = m * n;

        bool ok = true;
        FOR(i,2,n) if (a[i] % d != a[1] % d) ok = false;
        if (!ok) {
            cout << -1 << endl;
            continue;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) a[i] = a[i] / d;
        int to = a[n / 2 + n % 2];

        long long res = 0;
        FOR(i,1,n) res += abs(to - a[i]);
        cout << res << endl;
    }
    return 0;
}

