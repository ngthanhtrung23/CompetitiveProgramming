
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

int sum[44], sxor[44];
ll f[44][2];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    ll s, x;
    while (cin >> s >> x) {
        bool good = (s == x);
        FOR(bit,1,42) {
            sum[bit] = s % 2; s /= 2;
            sxor[bit] = x % 2; x /= 2;
        }
        memset(f, 0, sizeof f);
        f[0][0] = 1;

        FOR(i,0,41) FOR(rem,0,1) {
            ll cur = f[i][rem];
            if (!cur) continue;

            REP(a,2) REP(b,2) {
                int x = sxor[i+1];
                int s = sum[i+1];

                if ((a ^ b) != x) continue;
                if ((a + b + rem) % 2 != s) continue;

                int rem2 = (a + b + rem) / 2;
                f[i+1][rem2] += cur;
            }
        }
        ll res = f[42][0];
        if (good) res -= 2;
        cout << res << endl;
    }
}
