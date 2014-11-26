#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int n;
map<int,int> cnt;
const int MN = 1011;
const int MOD = 1000000007;

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1);
    mid = (mid * mid) % MOD;
    if (k & 1) return (mid * x) % MOD;
    else return mid;
}

long long inverse(long long x) {
    return power(x, MOD - 2);
}

long long gt[100111];

long long c(long long n, long long k) {
    return gt[n] * inverse(gt[k]) % MOD * inverse(gt[n-k]) % MOD;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    gt[0] = 1;
    FOR(i,1,100000) gt[i] = (gt[i-1] * i) % MOD;
    while (cin >> n) {
        cnt.clear();
        FOR(turn,1,n) {
            int a; cin >> a;
            for(int i = 2; i*i <= a; ++i)
                while (a % i == 0) {
                    cnt[i] += 1;
                    a /= i;
                }
            if (a > 1) cnt[a] += 1;
        }
        long long res = 1;
        for(auto p : cnt) {
            res = (res * c(n+p.second-1, p.second)) % MOD;
        }
        cout << res << endl;
    }
    return 0;
}
