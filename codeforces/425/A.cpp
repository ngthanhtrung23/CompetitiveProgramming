#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 211;

int n, a[MN], k;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];

        int res = -1000111000;
        FOR(l,1,n) FOR(r,l,n) {
            int len = r - l + 1;
            int other = n - len;

            multiset<int> x, y; x.clear(); y.clear();
            FOR(i,l,r) x.insert(a[i]);
            FOR(i,1,n) if (i < l || i > r) y.insert(-a[i]);

            FOR(i,1,min(min(len, other), k)) {
                int t = - (*y.begin()); y.erase(y.begin());
                x.insert(t);
                x.erase(x.begin());
            }

            int sum = 0;
            for(__typeof(x.begin()) it = x.begin(); it != x.end(); ++it)
                sum += *it;
            res = max(res, sum);
        }
        cout << res << endl;
    }
    return 0;
}
