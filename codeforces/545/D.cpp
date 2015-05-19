
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

int n, a[MN];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        multiset<int> s;
        FOR(i,1,n) {
            cin >> a[i];
            s.insert(a[i]);
        }
        long long cur = 0;
        int res = 0;
        FOR(i,1,n) {
            auto it = s.lower_bound(cur);
            if (it == s.end()) {
                it = s.begin();
            }
            if (*it >= cur) {
                ++res;
            }
            cur += *it;
            s.erase(it);
        }
        cout << res << endl;
    }
    return 0;
}
