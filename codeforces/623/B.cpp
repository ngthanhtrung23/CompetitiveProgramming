
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1000111;
const ll INF = 1e18;

int n, rem, change, a[MN];
ll f[MN], g[MN], r[MN];
ll res;

set<int> cached;
void solve(int x) {
    if (cached.count(x)) return ;

    FOR(i,1,n) {
        int t = a[i] % x;
        if (t == 0) f[i] = f[i-1];
        else if (t == 1 || t == x - 1) f[i] = f[i-1] + change;
        else f[i] = INF;
    }
    g[n+1] = 0;
    FORD(i,n,1) {
        int t = a[i] % x;
        if (t == 0) g[i] = g[i+1];
        else if (t == 1 || t == x - 1) g[i] = g[i+1] + change;
        else g[i] = INF;
    }

    r[n+1] = (n+1LL) * (ll) rem;
    FORD(j,n,1) {
        r[j] = g[j] + j * (ll) rem;
        r[j] = min(r[j], r[j+1]);
    }

    FOR(i,0,n) {
        ll cur = r[i+1];
        cur += f[i] - (i+1LL) * (ll) rem;
        res = min(res, cur);
    }
}

void go(int x) {
    for(int i = 2; i*i <= x; ++i)
        if (x % i == 0) {
            solve(i);
            while (x % i == 0) x /= i;
        }
    if (x > 1) solve(x);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d %d %d", &n, &rem, &change) == 3) {
        res = (n - 1LL) * rem;
        FOR(i,1,n) scanf("%d", &a[i]);
        cached.clear();

        // either a[1] or a[n] must be kept
        FOR(x,a[1]-1,a[1]+1) go(x);
        FOR(x,a[n]-1,a[n]+1) go(x);

        cout << res << endl;
    }
}
