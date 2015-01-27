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

int n, t, r, a[311];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);

    while (cin >> n >> t >> r) {
        FOR(i,1,n) {
            cin >> a[i];
        }
        --t;
        sort(a+1, a+n+1);

        set<int> s;
        set<int> used;
        int res = 0;
        bool can = true;
        FOR(i,1,n) {
            while (!s.empty() && *s.begin() + t < a[i]) s.erase(s.begin());

            while (s.size() < r) {
                ++res;
                int want = a[i];
                while (used.count(want)) --want;
                used.insert(want);

                if (want + t < a[i]) break;
                s.insert(want);
            }
            if (s.size() < r) {
                can = false;
                break;
            }
        }
        if (!can) res = -1;
        cout << res << endl;
    }
    return 0;
}
