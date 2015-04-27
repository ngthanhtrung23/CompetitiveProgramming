
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

#define _(X) ((X) & (-(X)))

int bit[20111], n, a[20111];

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

void update(int u) {
    while (u < 20111) {
        bit[u]++;
        u += _(u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int test; cin >> test;
    while (test--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];

        int res = 0;
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            res += get(a[i] + 31) - get(a[i] - 32);

            update(a[i]);
        }
        cout << res << endl;
    }
    return 0;
}
