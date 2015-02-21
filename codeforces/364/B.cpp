
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

int n, d, a[55], x[500111], nx;
bitset<500111> f[55];

int main() {
    while (scanf("%d%d", &n, &d) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);

        FOR(i,0,n) f[i].reset();
        f[0].set(0);
        FOR(i,1,n) f[i] = f[i-1] | (f[i-1] << a[i]);

        nx = 0;
        FOR(i,0,500000) if (f[n].test(i)) x[++nx] = i;
//        PR(x, nx);

        int u = 1, day = 0;
        while (u <= nx) {
            int v = u;
            while (v+1 <= nx && x[v+1] <= x[u] + d) ++v;

            if (u == v) break;
            else {
                u = v;
                ++day;
            }
        }

        cout << x[u] << ' ' << day << endl;
    }
    return 0;
}
