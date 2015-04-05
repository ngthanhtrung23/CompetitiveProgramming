
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

const int MN = 2000111;

int n, q;
ll a[MN], b;
int last[MN], f[MN], g[MN];

void solve() {
    int j = 0;
    ll sum = 0;
    FOR(i,1,n) {
        while (j < n+n && sum + a[j+1] <= b) {
            ++j;
            sum += a[j];
        }
        last[i] = j;
        sum -= a[i];
    }
//    DEBUG(b);
//    PR(last, n);

    FORD(i,n,1) {
        if (last[i] >= n) {
            f[i] = 1;
            g[i] = last[i] - n;
        }
        else {
            f[i] = f[last[i] + 1] + 1;
            g[i] = g[last[i] + 1];
        }
    }
//    PR(f, n);
//    PR(g, n);

    int res = n;
    FOR(i,1,n) {
        if (g[i] >= i-1)
            res = min(res, f[i]);
    }
    cout << res << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> q) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) a[n+i] = a[i];

        while (q--) {
            cin >> b;
            solve();
        }
    }
    return 0;
}
