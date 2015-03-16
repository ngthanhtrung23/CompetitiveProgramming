
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

int n;
int good[1011];

int main() {
    while (cin >> n) {
        memset(good, false, sizeof good);
        int i = 0; good[i] = true;
        REP(turn,n*n) {
            i = (i + turn + 1) % n;
            good[i] = true;
        }
        bool ok = true;
        REP(i,n) ok &= good[i];
        cout << (ok ? "YES" : "NO") << endl;
    }
    return 0;
}
