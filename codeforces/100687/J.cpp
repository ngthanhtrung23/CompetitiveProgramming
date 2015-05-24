
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

const int MN = 100111;
int n, a[MN], done[MN], b[MN];

bool check(int k) {
    // admins numbered from 0 --> k-1
    REP(i,k) done[i] = 0;

    FOR(i,1,n) {
        int t = i % k;
        int start = max(a[i], done[t]);

        b[i] = start + 15 * 60 - 1;
        done[t] = start + 15 * 60;
    }
    FOR(i,1,n) if (b[i] - a[i] >= 3 * 3600) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            int h, m, s; scanf("%d:%d:%d", &h, &m, &s);
            a[i] = h * 3600 + m * 60 + s;
        }
        sort(a+1, a+n+1);
        int l = 1, r = n, res = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}

