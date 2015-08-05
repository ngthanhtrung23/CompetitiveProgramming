
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

int n, k, a, sum[MN], x[MN], f[MN];

bool check(int q) {
    memset(sum, 0, sizeof sum);
    FOR(i,1,q) sum[x[i]]++;
    FOR(i,1,n) sum[i] += sum[i-1];

    f[0] = 0;
    FOR(i,1,n) {
        f[i] = f[i-1];
        if (i >= a && sum[i] == sum[i-a]) {
            int prev = (i == a) ? 0 : f[i-a-1];
            f[i] = max(f[i], prev + 1);
        }
    }
    return f[n] >= k;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k >> a) {
        int q; cin >> q;
        FOR(i,1,q) cin >> x[i];

        int l = 1, r = q, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        if (res == q) res = -1;
        else ++res;
        cout << res << endl;
    }
}

