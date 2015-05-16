
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

int main() {
    ios :: sync_with_stdio(false);
    int r1, c1, r2, c2;
    while (cin >> r1 >> c1 >> r2 >> c2) {
        if (r1 == r2 || c1 == c2) cout << 1; else cout << 2;
        cout << ' ';

        if ((r1 + c1) % 2 != (r2 + c2) % 2) cout << 0;
        else if (r1 + c1 == r2 + c2 || r1 - c1 == r2 - c2) cout << 1;
        else cout << 2;
        cout << ' ';

        cout << max(abs(r1 - r2), abs(c1 - c2)) << endl;
    }
    return 0;
}
