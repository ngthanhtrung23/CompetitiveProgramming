
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

int n, k, a[111];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        int color = 1;
        bool ok = true;

        vector<int> res[111];
        FOR(col,1,100) {
            bool need = false;
            FOR(i,1,n) if (a[i] >= col) { need = true; break; }
            if (!need) break;

            if (color > k) {
                ok = false;
                break;
            }

            int cnt = 0;
            FOR(i,1,n) if (a[i] >= col) {
                res[i].push_back(color);
                ++cnt;
            }
            if (cnt != n) ++color;
        }
        if (!ok) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        FOR(i,1,n) {
            for(int x : res[i]) cout << x << ' ';
            cout << endl;
        }
    }
    return 0;
}
