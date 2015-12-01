
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const ll MOD = 1e9 + 7;

const int MN = 1000111;
int visited[MN], p;
ll k;

ll power(ll x, ll k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    ll mid = power(x, k >> 1);
    mid = mid * mid % MOD;

    if (k & 1) return mid * x % MOD;
    return mid;
}

int main() {
    while (cin >> p >> k) {
        if (k == 0) cout << power(p, p-1) << endl;
        else if (k == 1) cout << power(p, p) << endl;
        else {
            memset(visited, 0, sizeof visited);
            int res = 0;
            FOR(i,1,p-1) if (!visited[i]) {
                ll u = i * (ll) k % p;
                visited[i] = 1;
                ++res;

                while (u != i) {
                    visited[u] = 1;
                    u = u * k % p;
                }
            }
            ll ans = power(p, res);
            ll cnt = 0;
            REP(f0,p)
                if (f0 == k * f0 % p) {
                    ++cnt;
                }
            cout << ans * cnt << endl;
        }
    }
}
