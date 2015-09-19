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

int gt[15];

int eulerPhi(int n) { // = n (1-1/p1) ... (1-1/pn)
   if (n == 0) return 0;
   int ans = n;
   for (int x = 2; x*x <= n; ++x) {
      if (n % x == 0) {
         ans -= ans / x;
         while (n % x == 0) n /= x;
      }
   }
   if (n > 1) ans -= ans / n;
   return ans;
}

ll power(ll x, int k, ll MOD) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    ll mid = power(x * x % MOD, k >> 1, MOD);

    if (k & 1) return mid * x % MOD;
    else return mid;
}

int get(int p, int m) {
    if (m == 1) return 1;

    int pk = 1;
    while (m % p == 0) m /= p, pk *= p;

    int t = get(p, eulerPhi(m));
    t = power(p, t, m);

    for(int x = 0; ; x += pk) {
        if (x % m == t) return x;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("limit.in", "r", stdin);
    freopen("limit.out", "w", stdout);

    gt[0] = 1;
    FOR(i,1,12) gt[i] = gt[i-1] * i;

    int p, m;
    while (cin >> p >> m) {
        cout << get(p, gt[m]) << endl;
    }
}