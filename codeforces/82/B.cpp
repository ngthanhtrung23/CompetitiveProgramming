
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

int n, nRes;
const int NBIT = 211;
bitset<NBIT + 1> a[211*211], all, res[211], contains[211];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        if (n == 2) {
            int k; scanf("%d", &k);
            int u; scanf("%d", &u);
            printf("%d %d\n", 1, u);
            printf("%d", k-1);

            FOR(i,2,k) {
                scanf("%d", &u);
                printf(" %d", u);
            }
            puts("");
            continue;
        }

        int k = n * (n-1) / 2;
        all.reset();
        REP(val,NBIT) {
            contains[val].reset();
            REP(j,NBIT) contains[val].set(j);
        }

        FOR(i,1,k) {
            a[i].reset();
            int cnt; scanf("%d", &cnt);
            while (cnt--) {
                int u; scanf("%d", &u);
                a[i].set(u);
            }
            all |= a[i];

            REP(val,NBIT) if (a[i].test(val)) {
                contains[val] &= a[i];
            }
        }

        REP(val,NBIT) if (all.test(val)) {
            printf("%d", contains[val].count());
            REP(j,NBIT) if (contains[val].test(j)) printf(" %d", j);
            puts("");
            all &= ~contains[val];
        }
    }
    return 0;
}

