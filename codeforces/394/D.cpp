#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 1011;

int n, a[MN];

bool check(int val, int &start, int &step) {
    FOR(d,0,20000) {
        int l = a[1] - val, r = a[1] + val;
        bool ok = true;
        FOR(i,2,n) {
            l += d; r += d;
            int u = a[i] - val, v = a[i] + val;
            
            if (v < l || r < u) {
                ok = false;
                break;
            }

            l = max(l, u); r = min(r, v);
        }

        if (ok) {
            step = d;
            start = r - d * (n-1);
            return true;
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);

        int l = 0, r = 10111, res = r;
        int start, step;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid, start, step)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        check(res, start, step);
        cout << res << endl << start << ' ' << step << endl;
    }
    return 0;
}
