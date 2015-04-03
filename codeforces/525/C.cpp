
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

int n, a[100111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);
        int cnt = 0, x = 0, y = 0;

        long long res = 0;
        FORD(i,n-1,1) {
            if (a[i] == a[i+1] || a[i] == a[i+1] - 1) {
                ++cnt;
                if (cnt == 1) x = a[i];
                else {
                    y = a[i];
                    res += x * (long long) y;
                    cnt = 0;
                }
                --i;
            }
        }
        cout << res << endl;
    }
    return 0;
}
