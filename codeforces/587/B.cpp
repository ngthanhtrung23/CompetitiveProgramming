
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

const int MN = 1000111;
const ll MOD = 1e9 + 7;

int n, k;
ll l;

int a[MN], c[MN], sc;
vector< vector<ll> > f;
ll cnt[MN], g[MN];

void RR() {
    sc = 0;
    FOR(i,1,n) c[i] = a[i];
    sort(c+1, c+n+1);
    sc = unique(c+1, c+n+1) - c - 1;

    FOR(i,1,n) a[i] = lower_bound(c+1, c+n+1, a[i]) - c;
}

int main() {
    while (cin >> n >> l >> k) {
        FOR(i,1,n) scanf("%d", &a[i]);
        RR();
//        PR(a, n);

        ll nSeg = l / n;
        if (l % n) ++nSeg;

        f.resize(k + 5);
        FOR(i,0,k) f[i].resize(n+5);

        f[0][0] = 1;
        g[0] = 1;
        ll res = 0;
        FOR(i,1,k) {
            FOR(j,0,n) cnt[j] = 0;
            FOR(j,0,n) cnt[ a[j] ] = (cnt[a[j]] + f[i-1][j]) % MOD;
            FOR(j,1,n) cnt[j] = (cnt[j-1] + cnt[j]) % MOD;

            FOR(j,1,n) f[i][j] = cnt[a[j]];

            g[i] = 0;
            FOR(j,1,n) g[i] = (g[i] + f[i][j]) % MOD;

            int len = i;
            // all from first nSeg-1 segments
            if (len <= nSeg-1) {
                res = (res + (nSeg-len) % MOD * g[len]) % MOD;
            }
            if (i <= nSeg) {
                int bound = l % n;
                if (bound == 0) bound = n;
                FOR(j,1,bound) {
                    res = (res + cnt[a[j]]) % MOD;
                }
            }
        }
        cout << res << endl;
    }
}

