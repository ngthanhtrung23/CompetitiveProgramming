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

int n, t;
pair<ll, ll> a[111];
ll p[111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].second >> a[i].first;
        sort(a+1, a+n+1);
        cin >> t;
        FOR(i,1,t) cin >> p[i];
        p[t+1] = 1e18;

        int j = 1;
        ll f = 1, res = 0, killed = 0;
        FOR(i,1,n) {
            while (killed + a[i].second >= p[j]) {
                ll add = p[j] - killed;
                res += a[i].first * add * f;
                killed += add;
                a[i].second -= add;

                ++j;
                ++f;
            }
            killed += a[i].second;
            res += a[i].first * a[i].second * f;
        }
        cout << res << endl;
    }
    return 0;
}

