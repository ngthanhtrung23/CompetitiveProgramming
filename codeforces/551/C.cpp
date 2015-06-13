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

int n, m, a[100111], b[100111];

bool check(long long val) {
    FOR(i,1,n) a[i] = b[i];

    int j = n;
    while (j > 0 && a[j] == 0) --j;

    FOR(turn,1,m) {
        long long cur = val - j;
        while (cur > 0) {
            long long can = min(cur, (long long) a[j]);
            cur -= can;
            a[j] -= can;

            while (j > 0 && a[j] == 0) --j;
            if (j == 0) return true;
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) b[i] = a[i];

        long long l = 0, r = 10001110001110001LL;
        long long res = r;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (check(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}
