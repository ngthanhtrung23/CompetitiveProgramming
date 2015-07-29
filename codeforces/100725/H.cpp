
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

int n, x[50111];

int main() {
    ios :: sync_with_stdio(false);
    freopen("highways.in", "r", stdin);
    freopen("highways.out", "w", stdout);

    while (cin >> n) {
        FOR(i,2,n) cin >> x[i];
        x[1] = 0;

        if (n < 4) cout << 0 << endl;
        else {
            long long res = 1e15;
            int save = -1;
            FOR(i,3,n-1) {
                long long cur = x[i] - x[1] + x[n] - x[i-1];
                if (cur < res) {
                    res = cur;
                    save = i;
                }
            }
            cout << res << endl;
            cout << save << ' ' << 1 << "  " << n << ' ' << save-1 << endl;
        }
    }
}
