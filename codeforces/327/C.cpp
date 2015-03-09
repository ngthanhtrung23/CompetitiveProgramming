
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

const int MN = 100111;
const long long MOD = 1e9 + 7;
char a[MN];
int k;

ll power(ll x, ll k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    ll mid = power(x * x % MOD, k >> 1);
    if (k & 1) return mid * x % MOD;
    else return mid;
}

ll inverse(ll x) {
    return power(x, MOD - 2);
}

int main() {
    while (scanf("%s", &a[1]) == 1) {
        cin >> k;
        int l = strlen(a+1);

        ll res = 0;
        ll x = power(2, l);
        FOR(i,1,l) if (a[i] == '0' || a[i] == '5') {
            res = (res + power(2, i-1) * (power(x, k) - 1 + MOD) % MOD * inverse(x-1)) % MOD;
        }
        cout << res << endl;
    }
    return 0;
}

