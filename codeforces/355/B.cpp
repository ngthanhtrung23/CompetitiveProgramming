
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int c1, c2, c3, c4, n, m, a[1011], b[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> c1 >> c2 >> c3 >> c4) {
        cin >> n >> m;
        int suma = 0, sumb = 0;
        FOR(i,1,n) { cin >> a[i]; suma += a[i]; }
        FOR(i,1,m) { cin >> b[i]; sumb += b[i]; }
        sort(a+1, a+n+1);
        sort(b+1, b+m+1);

        int res = c4;
        // use c3 for all buses
        int cur = 0;
        FOR(i,1,m) cur += min(b[i] * c1, c2);
        cur = min(cur, c3);
        cur += c3;
        res = min(res, cur);

        // use c3 for all trolleys
        cur = 0;
        FOR(i,1,n) cur += min(a[i] * c1, c2);
        cur = min(cur, c3);
        cur += c3;
        res = min(res, cur);

        // do not use c3
        cur = 0;
        FOR(i,1,n) cur += min(a[i] * c1, c2);
        FOR(i,1,m) cur += min(b[i] * c1, c2);
        res = min(res, cur);
        cout << res << endl;
    }
}

