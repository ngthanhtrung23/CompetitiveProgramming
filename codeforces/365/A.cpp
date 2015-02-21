
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

int n, k, a[111], cnt[11];

int main() {
    while (cin >> n >> k) {
        int res = 0;
        FOR(i,1,n) {
            cin >> a[i];
            memset(cnt, 0, sizeof cnt);
            if (a[i] == 0) cnt[0] = 1;
            else {
                while (a[i]) {
                    cnt[a[i] % 10]++;
                    a[i] /= 10;
                }
            }

            bool ok = true;
            FOR(x,0,k) if (!cnt[x]) ok = false;
            if (ok) ++res;
        }
        cout << res << endl;
    }
    return 0;
}
