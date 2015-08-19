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

int l[11];

int main() {
    int ntest; scanf("%d", &ntest);
    FOR(i,1,10) l[i] = (i*20) * (i*20);
    while (ntest--) {
        int n; scanf("%d", &n);
        int res = 0;
        while (n--) {
            int x, y; scanf("%d%d", &x, &y);
            int t = x*x + y*y;
            FOR(i,1,10) if (t <= l[i]) ++res;
        }
        printf("%d\n", res);
    }
    return 0;
}