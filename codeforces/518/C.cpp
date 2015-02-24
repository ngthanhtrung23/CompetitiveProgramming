
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

const int MN = 100111;
int n, m, k, need[MN], a[MN], pos[MN];

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        FOR(i,1,n) need[i] = (i - 1) / k + 1;
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            pos[a[i]] = i;
        }

//        PR(need, n);
//        PR(a, n);

        long long res = 0;
        while (m--) {
            int u; scanf("%d", &u);

            int x = pos[u];
            res += need[x];
            assert(a[x] == u);

            if (x > 1) {
                int v = a[x - 1];
                swap(a[x], a[x-1]);
                pos[a[x]] = x;
                pos[a[x-1]] = x-1;
            }

//            DEBUG(res);
        }
        cout << res << endl;
    }
    return 0;
}
