
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

const int MN = 2011;
int n, k, a[MN], f[MN];

bool check(long long val) {
    FORD(i,n,1) {
        f[i] = 1;
        FOR(j,i+1,n) if (abs(a[i] - a[j]) <= val * (j-i)) f[i] = max(f[i], f[j] + 1);
        if (f[i] >= n - k) return true;
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];

        long long l = 0, r = 2000111000, res = r;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (check(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}
