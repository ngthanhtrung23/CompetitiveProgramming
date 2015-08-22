
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
using namespace std;

ll con_sum(ll from, ll to) {
    ll k = to - from + 1;
    return (to + from) * k / 2;
}

ll count(ll b1, ll b2, ll S) {
    if (b1 < 0) return 0;
    if (b2 < 0) return 0;
    if (S < 0) return 0;
    if (b1 > b2) swap(b1, b2);

    if (b1 + b2 <= S) return (b1 + 1) * (b2 + 1);
    if (S <= b1) return con_sum(1, S + 1);
    if (S <= b2) return con_sum(S - b1 + 1, S + 1);
    
    ll t = S - b2;
    return (b2 + 1) * t + con_sum(S-b1 + 1, b2 + 1);
}

int main() {
    ios :: sync_with_stdio(false);
    ll a, b, c, l;
    while (cin >> a >> b >> c >> l) {
        // a + x >= b + y
        // a + x >= c + z
        ll res = 0;
        FOR(x,0,l) {
            res += count(a + x - b, a + x - c, l - x);
            res -= count(a + x - b, a + x - c, min(l-x, a + x - b - c));
        }
        // b + y >= c + z
        // b + y >  a + x
        FOR(y,0,l) {
            res += count(b + y - c, b + y - a - 1, l - y);
            res -= count(b + y - c, b + y - a - 1, min(l-y, b + y - a - c));
        }
        // c + z > a + x
        // c + z > b + y
        FOR(z,0,l) {
            res += count(c + z - a - 1, c + z - b - 1, l - z);
            res -= count(c + z - a - 1, c + z - b - 1, min(l-z, c + z - a - b));
        }
        cout << res << endl;
    }
}
