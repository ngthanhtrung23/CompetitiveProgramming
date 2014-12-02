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

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n, l, a[1011];
    while (cin >> n >> l) {
        FOR(i,1,n) cin >> a[i];
        int res = 0;
        sort(a+1, a+n+1);
        res = max(res, a[1] * 2);
        res = max(res, (l - a[n]) * 2);
        FOR(i,1,n-1) res = max(res, a[i+1] - a[i]);

        cout << res / 2 << '.' << (res % 2) * 5 << endl;
    }
    return 0;
}
