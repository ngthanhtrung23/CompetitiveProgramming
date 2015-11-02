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
#define SZ(X) ((int) ((X).size()))
using namespace std;

ll get(ll mid, int k) {
    ll res = 0;
    while (mid) {
        res += mid;
        mid /= k;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    ll n, k;
    while (cin >> n >> k) {
        ll l = 0, r = 1000111000111LL, res = r;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (get(mid, k) >= n) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << res << endl;
    }
}

