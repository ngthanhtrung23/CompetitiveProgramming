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

const int MN = 800111;

int n;
long double a[MN];

ll c2(ll n) {
    return n * (n-1) / 2ll;
}
ll c3(ll n) {
    return n * (n-1) * (n-2) / 6ll;
}

const long double PI = atan2((long double) 0.0, (long double) -1.0);
const long double EPS = 1e-18;

int main() {
    ios :: sync_with_stdio(false);
    int c, d;
    while (scanf("%d%d%d", &n, &c, &d) == 3) {
        FOR(i,1,n) {
            int x, y;
            scanf("%d%d", &x, &y);
            a[i] = atan2(y - d, x - c);
        }
        sort(a+1, a+n+1);

        ll res = c3(n);

        FOR(i,n+1,n+n+3) {
            a[i] = a[i-n];
            a[i] += 2 * PI;
        }

        int j = 1, l = 1, r = 1;
        FOR(i,1,n) {
            while (a[j+1] - a[i] < PI + EPS) ++j;
            while (a[l] - a[i] < PI - EPS) ++l;
            while (a[r+1] - a[i] < PI + EPS) ++r;

            res -= c2(j - i);
            res += c2(r - l + 1);
        }
//        DEBUG(res);
//        assert(res == save);
        cout << res << endl;
    }
}
