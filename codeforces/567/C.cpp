
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

int n;
ll k, a[200111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        map<ll, ll> after, before;
        FOR(i,1,n) after[a[i]] += 1;

        ll res = 0;
        FOR(i,1,n) {
            after[a[i]] -= 1;

            if (a[i] % k == 0) {
                res += before[a[i] / k] * after[a[i] * k];
            }

            before[a[i]] += 1;
        }
        cout << res << endl;
    }
}

