
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

ll lcm(ll a, ll b) {
    return a / __gcd(a, b) * b;
}

ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

ll solve(ll a, ll b) {
    ll x0, y0;
    ll d = extgcd(a, b, x0, y0);
    if (d > 1) return lcm(a, b);

    ll k = (b*y0 - a*x0) / (2*a/d*b);
    k = max(k, -x0 * d / b);

    ll x = x0 + k*b / d;
    ll y = y0 - k*a / d;

    while (a*x < 0) {
        x += b / d;
        y -= a / d;
    }
    while (a*x < b*y) {
        x += b / d;
        y -= a / d;
    }

    return a * x;
}

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
    ll a, b;
    while (cin >> a >> b) {
        if (a == 1 && b == 1) cout << 1 << endl;
        else if (a == 1 || b == 1) cout << 2 << endl;
        else cout << min(lcm(a, b), min(solve(a, b), solve(b, a))) << endl;
    }
}
