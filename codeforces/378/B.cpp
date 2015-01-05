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

const int MN = 200111;
int a[MN], b[MN], x[MN];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        int k = 0;
        FOR(i,1,n) {
            cin >> a[i] >> b[i];
            x[++k] = a[i];
            x[++k] = b[i];
        }
        sort(x+1, x+k+1);

        FOR(i,1,n) if (i <= n/2 || a[i] <= x[n]) cout << '1'; else cout << '0'; cout << endl;
        FOR(i,1,n) if (i <= n/2 || b[i] <= x[n]) cout << '1'; else cout << '0'; cout << endl;
    }
    return 0;
}
