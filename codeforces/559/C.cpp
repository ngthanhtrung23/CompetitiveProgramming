
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
const ll MOD = 1e9 + 7;

ll power(ll x, ll k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    ll mid = power(x * x % MOD, k >> 1);
    if (k & 1) return mid * x % MOD;
    else return mid;
}

int n;
ll gt[MN], rev_gt[MN];
int X, Y;
pair<int,int> a[MN];
ll f[2][MN];

ll c(int n, int k) {
    return gt[n] * rev_gt[k] % MOD * rev_gt[n-k] % MOD;
}

ll get(int j, int i) {
    int dx = a[i].first - a[j].first;
    int dy = a[i].second - a[j].second;

    return c(dx + dy, dx);
}


int main() {
    ios :: sync_with_stdio(false);
    gt[0] = 1; FOR(i,1,MN-1) gt[i] = gt[i-1] * i % MOD;
    FOR(i,0,MN-1) rev_gt[i] = power(gt[i], MOD - 2);

    while (cin >> X >> Y >> n) {
        a[1] = make_pair(1, 1);
        a[n+2] = make_pair(X, Y);
        FOR(i,2,n+1) cin >> a[i].first >> a[i].second;

        n += 2;
        sort(a+1, a+n+1);

        memset(f, 0, sizeof f);
        f[1][1] = 1;
        FOR(i,2,n) {
            FOR(j,1,i-1) if (a[j].first <= a[i].first && a[j].second <= a[i].second) {
                f[0][i] = (f[0][i] + f[1][j] * get(j, i)) % MOD;
                f[1][i] = (f[1][i] + f[0][j] * get(j, i)) % MOD;
            }
        }
        cout << (f[0][n] - f[1][n] + MOD) % MOD << endl;
    }
}

