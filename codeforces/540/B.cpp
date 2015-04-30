
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

int n, k, p, x, y;
int a[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k >> p >> x >> y) {
        FOR(i,1,n) cin >> a[i];

        int small = 0, equal = 0, big = 0;
        FOR(i,1,n) {
            if (a[i] == y) ++equal;
            else if (a[i] < y) ++small;
            else ++big;
        }

        int canAdd = n - k;
        int needAdd = max(0, (n+1)/2 - equal - big);

        if (canAdd < needAdd) cout << -1 << endl;
        else {
            FOR(i,k+1,n) {
                if (needAdd) {
                    a[i] = y;
                    --needAdd;
                }
                else a[i] = 1;
            }
            int sum = 0;
            FOR(i,1,n) sum += a[i];
            if (sum > x) cout << -1 << endl;
            else {
                FOR(i,k+1,n) cout << a[i] << ' ';
                cout << endl;
            }
        }
    }
    return 0;
}
