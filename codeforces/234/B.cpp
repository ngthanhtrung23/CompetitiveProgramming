
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

int n, k, a[1011], b[1011];

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (cin >> n >> k) {
        FOR(i,1,n) {
            cin >> a[i];
            b[i] = a[i];
        }
        sort(b+1, b+n+1, greater<int>());
        int bound = b[k];
        cout << bound << endl;
        FOR(i,1,n) {
            if (k == 0) break;
            if (a[i] >= bound) {
                cout << i << ' ';
                --k;
            }
        }
        cout << endl;
    }
    return 0;
}
