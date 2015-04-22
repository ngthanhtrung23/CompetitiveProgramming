
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

int f[200111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        memset(f, 0, sizeof f);
        set<int> s;
        long long res = 0;
        FOR(i,1,n) {
            int a; cin >> a;
            
            if (s.empty()) {
                f[a] = 1;
            }
            else if (a < *s.begin()) {
                int h = f[*s.begin()];
                res += h;
                f[a] = h + 1;
            }
            else if (a > *s.rbegin()) {
                int h = f[*s.rbegin()];
                res += h;
                f[a] = h + 1;
            }
            else {
                auto it = s.upper_bound(a);
                auto it2 = it; --it2;

                int h = max(f[*it], f[*it2]);
                res += h;
                f[a] = h + 1;
            }
            s.insert(a);
        }
        cout << res << endl;
    }
    return 0;
}
