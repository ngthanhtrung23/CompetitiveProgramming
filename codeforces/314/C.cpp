
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

int n, a[100111], last[1000111];

#define _(X) ((X) & (-(X)))

const long long MOD = 1e9 + 7;
long long bit[1000111], f[100111];
void update(int x, long long val) {
    for(int u = x; u <= 1000000; u += _(u))
        bit[u] = (bit[u] + val) % MOD;
}

long long get(int x) {
    long long res = 0;
    for(int u = x; u > 0; u -= _(u))
        res = (res + bit[u]) % MOD;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    // next(i) = first number on the left of i that has equal value to a(i)
    // f(i)    = sum( product of all increasing sequences ending at i )
    //
    // 1 2 3 4 5
    // f(1) = 1
    // f(2) = 2 * (1 + f(1)) = 4
    // f(3) = 3 * (1 + f(1) + f(2)) = 18
    // f(4) = 4 * (1 + f(1) + f(2) + f(3)) = 96
    // f(5) = 5 * (1 + 1 + 4 + 18 + 96) = 600
    //
    // 1 2 2
    // f(1) = 1
    // f(2) = 2 * (1 + f(1)) = 4
    // f(3) = 2 * (1 + f(1) + f(2)) = 12

    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        memset(last, 0, sizeof last);

        memset(bit, 0, sizeof bit);
        long long res = 0;
        FOR(i,1,n) {
            f[i] = ((1LL + get(a[i])) * a[i] - get(a[i]) + MOD + get(a[i]-1)) % MOD;
            update(a[i], f[i]);

            res = (res + f[i]) % MOD;
        }
        cout << res << endl;
    }
    return 0;
}

