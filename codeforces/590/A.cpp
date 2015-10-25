
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 500111;
#define fixed fixed__
int n, a[MN], fixed[MN], res[MN], max_time;

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        memset(fixed, 0, sizeof fixed);
        fixed[1] = fixed[n] = 1;
        FOR(i,2,n-1)
            if (a[i] == a[i-1] || a[i] == a[i+1]) {
                fixed[i] = 1;
            }
//        PR(fixed, n);
        max_time = 0;

        FOR(i,1,n) if (fixed[i]) res[i] = a[i];

        int i = 1;
        while (i < n) {
            int j = i + 1;
            while (!fixed[j]) ++j;

            int cur = 0;
            for(int u = i+1, v = j-1; u <= v; ++u, --v) {
                ++cur;
                res[u] = res[u-1];
                res[v] = res[v+1];
            }
            i = j;
            max_time = max(max_time, cur);
        }

        printf("%d\n", max_time);
        FOR(i,1,n) printf("%d ", res[i]);
        puts("");
    }
}
