
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}
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

int powMod(int x, int k, int mod) {
    int res = 1;
    while (k > 0) {
        if (k & 1) res = res * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return res % mod;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);
    int n, k;
    while (GI(n) == 1 && GI(k) == 1) {
        int res;
        if (n <= 10) {
            int x = 1<<n;
            res = (powMod(2, x, k) + 1) % k;
        }
        else {
            int kk = k, p2 = 1;
            while (kk % 2 == 0) kk /= 2, p2 *= 2;
            int phi = eulerPhi(kk);

            int x = powMod(2, n, phi);
            int t = powMod(2, x, kk);

            for(int i = 0; i < k; i += p2) {
                if (i % kk == t) {
                    res = (i + 1) % k;
                    break;
                }
            }
        }
        cout << res << endl;
    }
}
