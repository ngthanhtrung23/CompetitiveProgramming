
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

int a, sum[4011];
ll cnt[100111];
string s;
int n;

int main() {
    while (cin >> a >> s) {
        n = s.length();
        s = ' ' + s;
        FOR(i,1,n) sum[i] = sum[i-1] + (s[i] - '0');
//        PR(sum, n);

        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) FOR(j,1,i) cnt[sum[i] - sum[j-1]]++;

        ll res = 0;
        if (a == 0) {
            res += cnt[0] * n * (n+1LL);
            res -= cnt[0] * cnt[0];
        }
        else {
            for(int x = 1; x*x <= a; ++x)
                if (a % x == 0 && a/x < 100111) {
                    res += cnt[x] * cnt[a / x];
                    if (x * x != a) res += cnt[a/x] * cnt[x];
                }
        }
        cout << res << endl;
    }
    return 0;
}
