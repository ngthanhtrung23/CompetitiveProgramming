
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

int n, a[111];

int main() {
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        if (n <= 2 || n % 2 == 0) cout << -1 << endl;
        else {
            int res = 0;
            FORD(i,n,1) if (a[i]) {
                int x;
                if (i / 2) {
                    x = i / 2;
                }
                else {
                    x = i;
                }
                int add = a[i];

                res += add;
                a[x] = max(0, a[x] - add);
                a[2*x] = max(0, a[2*x] - add);
                a[2*x+1] = max(0, a[2*x+1] - add);
            }
            cout << res << endl;
        }
    }
    return 0;
}

