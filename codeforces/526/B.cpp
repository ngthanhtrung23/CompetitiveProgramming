
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

int n, a[5011], f[5011], last, first;
long long res;

void dfs(int u, int need) {
    if (u*2 <= last) {
        int x = u*2;
        res += need - f[x];
        dfs(x, f[x]);

        x = u*2 + 1;
        res += need - f[x];
        dfs(x, f[x]);
    }
}

int main() {
    while (cin >> n) {
        last = (1 << (n+1)) - 1;
        FOR(i,2,last) cin >> a[i];

        first = 1<<n;

        FOR(i,first,last) {
            f[i] = 0;
            int u = i;
            while (u > 1) {
                f[i] += a[u];
                u /= 2;
            }
        }
        FORD(i,first-1,1) f[i] = max(f[i*2], f[i*2+1]);

//        PR(f, last);
        res = 0;
        dfs(1, f[1]);
        cout << res << endl;
    }
    return 0;
}
