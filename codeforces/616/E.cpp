
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const ll MOD = 1e9 + 7;

ll mult(ll a, ll b) {
    a %= MOD;
    b %= MOD;
    return a * b % MOD;
}
ll add(ll a, ll b) {
    a %= MOD;
    b %= MOD;
    return (a + b) % MOD;
}
ll sub(ll a, ll b) {
    a %= MOD;
    b %= MOD;
    return (a - b + MOD) % MOD;
}

long long summod(ll n, ll k) {
    if (k > n) {
        return add(mult(k - n, n), summod(n, n));
    }

    long long s=0;
    for (ll i=1; i<=k;) {
        ll q = n / i;
        ll r = min(k, n / q);
        ll t = r - i + 1;

        s = add(s, mult(n%i, t));
        ll x = t, y = t - 1LL;
        if (x % 2 == 0) x /= 2;
        else y /= 2;
        s = sub(s, mult(mult(x, y), q));

        i=r+1LL;
        assert(s < MOD);
    }
    return s;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    ll n, m;
    while (cin >> n >> m) {
        cout << summod(n, m) << endl;
    }
}
