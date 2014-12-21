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

int n, k, a[100111], cnt[100111];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) cin >> a[i];
        n = unique(a+1, a+n+1) - a - 1;
        FOR(i,1,n) {
            cnt[a[i]] += (i == 1 || i == n) ? 1 : ((a[i-1] == a[i+1]) ? 2 : 1);
        }
        int res = 1;
        FOR(i,2,k)
            if (cnt[i] > cnt[res]) res = i;
        cout << res << endl;
    }
    return 0;
}
