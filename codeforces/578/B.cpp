
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

const int MN = 200111;

#define left left__
#define right right__
ll a[MN], left[MN], right[MN];
ll x, k;

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n >> k >> x) {
        FOR(i,1,n) cin >> a[i];

        ll px = 1;
        FOR(i,1,k) px *= x;

        FOR(i,1,n) left[i] = left[i-1] | a[i];
        right[n+1] = 0;
        FORD(i,n,1) right[i] = right[i+1] | a[i];

        ll res = 0;
        FOR(i,1,n) res = max(res, (a[i] * px) | left[i-1] | right[i+1]);

        cout << res << endl;
    }
}
