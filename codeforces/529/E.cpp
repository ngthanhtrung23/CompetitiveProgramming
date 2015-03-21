
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

const int MN = 5011;
int a[MN], n, k;
bool has[10111000];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        memset(has, 0, sizeof has);
        FOR(i,1,n) {
            cin >> a[i];
            has[a[i]] = true;
        }
        int q; cin >> q;
        while (q--) {
            int need; cin >> need;

            int can = 1000111000;
            FOR(i,1,n) FOR(x,1,k) {
                int left = need - a[i] * x;
                if (left < 0) break;

                if (left == 0) {
                    can = min(can, x);
                }

                FOR(y,1,k-x) {
                    if (left % y == 0 && left / y < 10111000 && has[left / y])
                        can = min(can, x + y);
                }
            }
            if (can > k) cout << -1 << endl;
            else cout << can << endl;
        }
    }
    return 0;
}
