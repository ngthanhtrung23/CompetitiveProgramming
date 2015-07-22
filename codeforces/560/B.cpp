
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

int a[5], b[5];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a[1] >> b[1]) {
        cin >> a[2] >> b[2] >> a[3] >> b[3];
        bool ok = false;
        REP(r2,2) {
            REP(r3,2) {
                if (a[2] + a[3] <= a[1] && max(b[2], b[3]) <= b[1]) ok = true;
                if (b[2] + b[3] <= b[1] && max(a[2], a[3]) <= a[1]) ok = true;
                swap(a[3], b[3]);
            }
            swap(a[2], b[2]);
        }
        cout << (ok ? "YES" : "NO") << endl;
    }
}
