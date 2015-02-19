
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

#define ll long long
const ll MOD = 7340033;

ll f[33][1011], g[5][1011];

void init() {
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    FOR(i,1,30) {
        f[i][0] = 1;

        memset(g, 0, sizeof g);
        g[0][1] = 1;
        REP(t,4) FOR(cur,1,1000)
            if (g[t][cur])
                FOR(add,0,1000-cur)
                    g[t+1][cur+add] = (g[t+1][cur+add] + g[t][cur] * f[i-1][add]) % MOD;

        FOR(j,1,1000)
            f[i][j] = g[4][j];
    }
}

int main() {
    init();
    int q; scanf("%d", &q);
    while (q--) {
        int n, k; scanf("%d%d", &n, &k);
        if (k == 0) {
            puts("1");
            continue;
        }

        int can = 0;
        while (n > 1 && n % 2 == 1) {
            n /= 2;
            ++can;
        }
        printf("%d\n", (int) f[can][k]);
    }
    return 0;
}
