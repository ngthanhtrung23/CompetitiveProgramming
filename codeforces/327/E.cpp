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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

const int MOD = 1e9 + 7;
int n, a[24], f[TWO(24)], x[11], sum[TWO(24)];

int main() {
    while (scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            sum[ 1<<i ] = a[i];
        }
        int k; scanf("%d", &k);
        x[0] = x[1] = -1;
        for(int i = 0; i < k; ++i) scanf("%d", &x[i]);

        f[0] = 1;
        REP(mask,TWO(n)) {
            if (__builtin_popcount(mask) > 1) {
                int u = mask & (-mask);
                sum[mask] = sum[mask - u] + sum[u];
            }
            if (sum[mask] == x[0] || sum[mask] == x[1]) {
                f[mask] = 0;
                continue;
            }

            for(int i = 0; i < n; ++i)
                if (!CONTAIN(mask,i)) {
                    f[mask + TWO(i)] += f[mask];
                    if (f[mask + TWO(i)] >= MOD)
                        f[mask + TWO(i)] -= MOD;
                }
        }
        cout << f[TWO(n) - 1] << endl;
    }
    return 0;
}

