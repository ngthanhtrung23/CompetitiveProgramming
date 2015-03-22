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

int a[5011];

int main() {
    ios :: sync_with_stdio(false);
    int n, k;
    while (cin >> n >> k) {
        unordered_set<int> exist;
        FOR(i,1,n) {
            cin >> a[i];
            exist.insert(a[i]);
        }
        int q; cin >> q;
        while (q--) {
            int x; cin >> x;
            int res = k + 1;
            FOR(i,1,n) FOR(u,1,k) {
                if (a[i] * u == x) res = min(res, u);
                else if (a[i] * u > x) break;
                else {
                    FOR(v,1,k-u) {
                        int cur = x - a[i] * u;
                        if (cur % v == 0 && exist.count(cur/v))
                            res = min(res, u + v);
                    }
                }
            }
            if (res > k) cout << -1;
            else cout << res;
            cout << endl;
        }
    }
    return 0;
}
