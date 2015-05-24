
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
    int n;
    while (scanf("%d", &n) == 1) {
        bool ok = true;
        FOR(i,1,n) {
            int h, m, s;
            scanf("%d:%d:%d", &h, &m, &s);
            int x = h * 3600 + m * 60 + s;

            scanf("%d:%d:%d", &h, &m, &s);
            int y = h * 3600 + m * 60 + s;

            if (y - x >= 3 * 3600) ok = false;
        }
        cout << (ok ? "Yes" : "No") << endl;
    }
    return 0;
}

