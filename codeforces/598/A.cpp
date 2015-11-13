
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

ll get(ll l, ll r) {
    if (l > r) return 0;
    return (r + l) * (r - l + 1) / 2;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        ll n; cin >> n;
        ll sum = 0;
        ll last = 0;
        for(ll bound = 1; bound <= n; bound *= 2) {
            sum += get(last+1, bound - 1);
            sum -= bound;

            last = bound;
        }
        if (last < n) {
            sum += get(last+1, n);
        }
        cout << sum << endl;
    }
}
