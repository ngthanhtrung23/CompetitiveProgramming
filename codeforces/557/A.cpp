
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

int main() {
    ios :: sync_with_stdio(false);
    int a[5], b[5], n;
    while (cin >> n) {
        FOR(i,1,3) cin >> a[i] >> b[i];

        int x[5];
        x[1] = min(n - a[2] - a[3], b[1]);
        n -= x[1];

        x[2] = min(n - a[3], b[2]);
        n -= x[2];

        x[3] = n;
        cout << x[1] << ' ' << x[2] << ' ' << x[3] << endl;
    }
}
