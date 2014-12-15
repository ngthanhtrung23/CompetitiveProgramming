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

const long long MOD = 1000000007;
int n;
long long a[100111];

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1);
    mid = mid * mid % MOD;
    if (k & 1) return mid * x % MOD;
    else return mid;
}

long long inverse(long long x) {
    return power(x, MOD - 2);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n; FOR(i,1,n) cin >> a[i];

        map<long long,int> cnt;
        int res = 0;
        FOR(i,1,n) {
            long long need = inverse(a[i]);
            if (cnt.count(need) && cnt[need] > 0) {
                cnt[need] -= 1;
                ++res;
            }
            else cnt[a[i]] += 1;
        }
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}
